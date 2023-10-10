#include <robot.h>
#include <message_template.h>
#include <factory.hpp>

#define OHTOAI_DEFINE_CLASS(x)                                                    \
    public:                                                                       \
        virtual const char* class_name() const { return static_class_name(); }    \
        static constexpr const char* static_class_name() { return (#x); }

namespace ohtoai::vnotice
{
    class client
    {
        OHTOAI_DEFINE_CLASS(client)
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

        static auto create(const std::string& _class_name) {
            return ohtoai::ProductFactory<client>::instance().product(_class_name);
        }

        static auto has(const std::string& _class_name) {
            return ohtoai::ProductFactory<client>::instance().hasProduct(_class_name);
        }

        static auto get_names() {
            return ohtoai::ProductFactory<client>::instance().getProductNames();
        }
    };
}
