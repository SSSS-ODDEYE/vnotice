#include "http_client.h"
#include <spdlog/spdlog.h>

namespace ohtoai::vnotice
{
    class qywechat_client : public http_client
    {
        OHTOAI_DEFINE_CLASS(qywechat_client)
    private:
    public:
        qywechat_client() {
            config_http_url("https://qyapi.weixin.qq.com", "/cgi-bin/webhook/send?key={robot.id}");
        }
        void send(const robot &r, const message_template &m, const nlohmann::json &d) override {
            spdlog::info("qywechat_client::send: robot: {}", nlohmann::json(r).dump());
            http_client::send(r, m, d);
        }
    };
    OHTOAI_CLIENT_REGISTER(qywechat_client)
}
