#include "http_client.h"
#include <spdlog/spdlog.h>

namespace ohtoai::vnotice {
    class feishu_client : public http_client {
        OHTOAI_DEFINE_CLASS(feishu_client)
    private:
    public:
        feishu_client() {
            config_http_url("https://open.feishu.cn", "/open-apis/bot/v2/hook/{robot.id}");
        }
        void send(const robot &r, const message_template &m, const nlohmann::json &d) override {
            spdlog::info("feishu_client::send: robot: {}", nlohmann::json(r).dump());
            http_client::send(r, m, d);
        }
    };
    OHTOAI_CLIENT_REGISTER(feishu_client)
}
