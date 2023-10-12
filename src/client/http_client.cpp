#include "http_client.h"
#include <spdlog/spdlog.h>
#include <inja/inja.hpp>

namespace ohtoai::vnotice {
    OHTOAI_CLIENT_REGISTER(http_client)
}

void ohtoai::vnotice::http_client::config_http_url(const std::string &scheme_host_port, const std::string &path_template, HTTP_METHOD method) {
    logger()->debug("call {} (scheme_host_port: {}, path_template: {}, method: {})", __func__, scheme_host_port, path_template, method == GET ? "GET" : "POST)");
    this->scheme_host_port = scheme_host_port;
    this->path_template = path_template;
    this->method = method;
    cli = std::make_shared<httplib::Client>(scheme_host_port.c_str());
    cli->set_logger([this](const httplib::Request &req, const httplib::Response &res) {
        logger()->debug("{} {} {}", req.method, req.path, res.status);
    });
}

void ohtoai::vnotice::http_client::send(const robot &r, const message_template &m, const nlohmann::json &d) {
    logger()->debug("call {} (\n\trobot: {}, \n\tmessage: {}, \n\tdata: {})", __func__, nlohmann::json(r).dump(), nlohmann::json(m).dump(), nlohmann::json(d).dump());

    if (cli == nullptr) {
        logger()->error("{}: cli is nullptr", __func__);
        return;
    }

    auto path = inja::render(path_template, r);
    httplib::Result ret;

    switch (method) {
        case GET:
            logger()->debug("{}: GET {}:{} {}", __func__, cli->host(), cli->port(), path);
            ret = cli->Get(path);
            break;
        case POST:
        {
            auto body = inja::render(m.content, d);
            logger()->debug("{}: POST {}:{} {}, {}", __func__, cli->host(), cli->port(), path, body);
            ret = cli->Post(path, body, "application/json");
            break;
        }
        default:
            logger()->error("{}: unknown method: {}", __func__, (int)method);
            break;
    }
    if(ret) {
        logger()->info("{}: status_code: {}", __func__, ret->status);
        logger()->info("{}: body: \"{}\"", __func__, ret->body);
    }
    else {
        logger()->error("{}: ret is nullptr", __func__);
    }
}
