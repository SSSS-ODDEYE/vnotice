#include "client.h"
#include <memory>
#include <httplib.h>

namespace httplib {
    class Client;
}

namespace ohtoai::vnotice {
    class http_client : public client {
        OHTOAI_DEFINE_CLASS(http_client)
    public:
        enum HTTP_METHOD {GET, POST};
    private:
        std::shared_ptr<httplib::Client> cli = nullptr;
        std::string scheme_host_port;
        std::string path_template;
        HTTP_METHOD method;
    public:

        /// @brief set http url of robot
        /// @param url_template e.g.: https://qyapi.weixin.qq.com/cgi-bin/webhook/send?key={{id}}
        /// @param method http method GET/POST
        void config_http_url(const std::string &url_template, HTTP_METHOD method = POST);

        /// @brief Send message to robot
        /// @param r robot
        /// @param m message
        /// @param d data
        void send(const robot &r, const message_template &m, const nlohmann::json &d) override;
    };
}
