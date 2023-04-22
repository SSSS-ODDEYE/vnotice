#include "../inc/robot.h"
#include "../inc/message_template.h"
#include <factory.hpp>

namespace ohtoai::vnotice
{
    class client
    {
    private:
        /* data */
    public:
        client() = default;
        virtual ~client() = default;

        /// @brief Send message to robot
        /// @param r specify the robot
        /// @param m specify the message template
        /// @param d data from runtime
        virtual void send(const robot &r, const message_template &m, const nlohmann::json &d) = 0;
    };

    using client_factory = ProductFactory<client>;
}
