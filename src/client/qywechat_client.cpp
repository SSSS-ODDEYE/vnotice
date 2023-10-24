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
            config_http_url("https://qyapi.weixin.qq.com/cgi-bin/webhook/send?key={{id}}");
        }
        void send(const robot &r, const message_template &m, const nlohmann::json &d) override {
            logger()->debug("call {} (\n\trobot: {}, \n\tmessage: {}, \n\tdata: {})", __func__, nlohmann::json(r).dump(), nlohmann::json(m).dump(), nlohmann::json(d).dump());
            http_client::send(r, m, d);
        }
    };
    OHTOAI_CLIENT_REGISTER(qywechat_client)
}
