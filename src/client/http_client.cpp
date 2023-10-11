#include "http_client.h"
#include <spdlog/spdlog.h>
#include <inja/inja.hpp>

namespace ohtoai::vnotice {
    OHTOAI_CLIENT_REGISTER(http_client)
}

void ohtoai::vnotice::http_client::config_http_url(const std::string &scheme_host_port, const std::string &path_template) {
    SPDLOG_DEBUG("http_client::config_http_url");
    cli = std::make_unique<httplib::Client>(scheme_host_port.c_str());
    this->path_template = path_template;
}

void ohtoai::vnotice::http_client::send(const robot &r, const message_template &m, const nlohmann::json &d) {
    SPDLOG_DEBUG("http_client::send: robot: {}", nlohmann::json(r).dump());
    SPDLOG_DEBUG("http_client::send: message: {}", nlohmann::json(m).dump());
    SPDLOG_DEBUG("http_client::send: data: {}", nlohmann::json(d).dump());

    if (cli == nullptr) {
        spdlog::error("http_client::send: cli is nullptr");
        return;
    }

    auto ret = cli->Post(inja::render(path_template, r).c_str(), inja::render(m.content, d), "application/json");
    if(ret) {
        spdlog::info("http_client::send: status_code: {}", ret->status);
        spdlog::info("http_client::send: body: {}", ret->body);
    }
    else {
        spdlog::error("http_client::send: ret is nullptr");
    }
}
