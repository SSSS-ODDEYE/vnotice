#include "http_client.h"
#include <spdlog/spdlog.h>
#include <inja/inja.hpp>

namespace ohtoai::vnotice {
    OHTOAI_CLIENT_REGISTER(http_client)
}

void ohtoai::vnotice::http_client::config_http_url(const std::string &scheme_host_port, const std::string &path_template, HTTP_METHOD method) {
    this->scheme_host_port = scheme_host_port;
    this->path_template = path_template;
    this->method = method;
    cli = std::make_shared<httplib::Client>(scheme_host_port.c_str());
    cli->set_logger([this](const httplib::Request &req, const httplib::Response &res) {
        if (res.status == 200) {
            logger()->debug("{} | {} | {}", res.status, req.method, req.path);
        }
        else if (res.status > 200 && res.status < 300) {
            logger()->warn("{} | {} | {}", res.status, req.method, req.path);
        }
        else {
            logger()->error("{} | {} | {}\n\t{}", res.status, req.method, req.path, res.body);
        }
    });
}

void ohtoai::vnotice::http_client::send(const robot &r, const message_template &m, const nlohmann::json &d) {
    if (cli == nullptr) {
        logger()->error("Client url is empty, need config http url first.");
        return;
    }

    auto path = inja::render(path_template, r);
    httplib::Result ret;

    switch (method) {
        case GET:
            ret = cli->Get(path);
            break;
        case POST:
        {
            auto body = inja::render(m.content, d);
            ret = cli->Post(path, body, "application/json");
            break;
        }
        default:
            logger()->error("Unknown method: {}", static_cast<int>(method));
            break;
    }

    if(!ret) {
        logger()->error("Cannot access {}:{}", cli->host(), cli->port());
    }
}
