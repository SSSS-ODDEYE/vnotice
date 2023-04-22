#include "client.h"
#include <spdlog/fmt/fmt.h>

namespace ohtoai::vnotice
{
    class qywechat_client : public client
    {
    private:
    public:
        void send(const robot &r, const message_template &m, const nlohmann::json &d) override
        {
            fmt::print("qywechat_client::send\n");
        }
    };
    static ohtoai::ProductRegistrar<ohtoai::vnotice::client, ohtoai::vnotice::qywechat_client> registrar("qywechat");
}
