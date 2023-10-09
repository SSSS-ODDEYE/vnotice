#include "client.h"
#include <memory>
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <cpp-httplib/httplib.h>

namespace httplib
{
    class Client;
}

namespace ohtoai::vnotice
{
    class http_robot_client : public client
    {
        OHTOAI_DEFINE_CLASS(http_robot_client)
    private:
        std::unique_ptr<httplib::Client> cli;
        std::string path_template;
    public:

        /// @brief set http url of robot
        /// @param scheme_host_port e.g.: https://qyapi.weixin.qq.com
        /// @param path_template e.g.: /cgi-bin/webhook/send?key={robot.id}
        void config_http_url(const std::string &scheme_host_port, const std::string &path_template);

        /// @brief Send message to robot
        /// @param r robot
        /// @param m message
        /// @param d data
        void send(const robot &r, const message_template &m, const nlohmann::json &d) override;
    };
}
