#include "http_robot_client.h"
#include <spdlog/spdlog.h>

namespace ohtoai::vnotice
{
    class feishu_client : public http_robot_client
    {
        OHTOAI_DEFINE_CLASS(feishu_client)
    private:
    public:
        feishu_client()
        {
            config_http_url("https://open.feishu.cn", "/open-apis/bot/v2/hook/{robot.id}");
        }
        void send(const robot &r, const message_template &m, const nlohmann::json &d) override
        {
            spdlog::info("feishu_client::send: robot: {}", nlohmann::json(r).dump());
            http_robot_client::send(r, m, d);            
        }
    };
    inline static ohtoai::ProductRegistrar<ohtoai::vnotice::client, ohtoai::vnotice::feishu_client> registrar(feishu_client::static_class_name());
}
