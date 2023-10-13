#include "http_client.h"
#include <catch2/catch_test_macros.hpp>
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>

static auto _init = []{
    auto logger = spdlog::stdout_color_mt("test");
    spdlog::set_default_logger(logger);
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[%H:%M:%S.%e] %^%L%$ %t [%n] | %v");
    return logger;
}();

TEST_CASE("Setup local server and send message to it") {
    httplib::Server svr;
    std::atomic_bool message_received {false};

    ohtoai::vnotice::robot robot;
    robot.id = "test-robot-id";
    robot.alias = "test-robot-alias";
    robot.type = "test-robot-type";

    ohtoai::vnotice::message_template message_template;
    message_template.alias = "test-message-alias";
    message_template.content = "test-message-content";
    message_template.type = "test-message-type";

    auto data = nlohmann::json{{"test-data-key", "test-data-value"}};

    svr.set_logger([](const httplib::Request &req, const httplib::Response &res) {
        if (res.status == 200) {
            spdlog::debug("{} | {} | {}", res.status, req.method, req.path);
        }
        else if (res.status > 200 && res.status < 300) {
            spdlog::warn("{} | {} | {}", res.status, req.method, req.path);
        }
        else {
            spdlog::error("{} | {} | {}\n\t{}", res.status, req.method, req.path, res.body);
        }
    });

    svr.Post("/api/v1/send/:robot_id", [&message_received, &robot, &message_template](const httplib::Request &req, httplib::Response &res) {
        spdlog::debug("server received message: {}", req.body);
        auto robot_id = req.path_params.at("robot_id");
        REQUIRE(robot_id == robot.id);
        REQUIRE(req.body == message_template.content);
        res.set_content("ok", "text/plain");
        message_received = true;
    });
    svr.Get("/alive", [](const httplib::Request &req, httplib::Response &res) {
        spdlog::debug("server received alive request");
        res.set_content("ok", "text/plain");
    });

    auto port = svr.bind_to_any_port("0.0.0.0");
    spdlog::debug("server listen: {}", port);

    auto t = std::thread([&svr]() {
        svr.listen_after_bind();
        spdlog::debug("server stopped");
    });

    svr.wait_until_ready();
    spdlog::debug("server started");

    auto http_client = ohtoai::vnotice::client::create<ohtoai::vnotice::http_client>("http_client");
    REQUIRE(http_client != nullptr);
    auto scheme_host_port = fmt::format("http://127.0.0.1:{}/api/v1/send/{{{{id}}}}", port);
    spdlog::debug("http client url: {}", scheme_host_port);
    http_client->config_http_url(scheme_host_port, ohtoai::vnotice::http_client::POST);
    spdlog::debug("http client configured");

    http_client->send(robot, message_template, data);
    spdlog::debug("message sent");

    for(int wait_time = 0; wait_time < 20; wait_time++) {
        if(message_received) {
            break;
        }
        spdlog::debug("waiting for message to be received");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    REQUIRE(message_received);
    svr.stop();
    while (svr.is_running()) {
        spdlog::debug("waiting for server to stop");
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    t.join();
}
