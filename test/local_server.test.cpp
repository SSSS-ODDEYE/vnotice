#include <catch2/catch.hpp>
#include <spdlog/fmt/fmt.h>
#include <spdlog/spdlog.h>
#include "client/http_client.h"

TEST_CASE("Setup local server and send message to it") {
    httplib::Server svr;
    spdlog::set_level(spdlog::level::debug);
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
        spdlog::debug("svr {} {} {}", req.method, req.path, res.status);
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

    httplib::Client cli(fmt::format("http://127.0.0.1:{}", port));
    auto ret = cli.Get("/alive");
    REQUIRE(ret);
    REQUIRE(ret->status == 200);
    REQUIRE(ret->body == "ok");

    auto http_client = ohtoai::vnotice::client::create<ohtoai::vnotice::http_client>("http_client");
    REQUIRE(http_client != nullptr);
    http_client->config_http_url(fmt::format("http://127.0.0.1:{}", port), "/api/v1/send/{{id}}", ohtoai::vnotice::http_client::POST);
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
    if (t.joinable()) {
        t.join();
    }
}
