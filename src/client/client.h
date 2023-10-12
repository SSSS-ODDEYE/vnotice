#include <robot.h>
#include <message_template.h>
#include <factory.hpp>
#include <spdlog/spdlog-inl.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#if defined(_DEBUG)
#define OHTOAI_DEFINE_CLASS(x)                                                                  \
    public:                                                                                     \
        virtual const char* class_name() const { return static_class_name(); }                  \
        static constexpr const char* static_class_name() { return (#x); }                       \
        static auto logger() {                                                                  \
            static auto _logger = [](const std::string& logger_name){                           \
                auto logger = spdlog::get(logger_name);                                         \
                if (logger == nullptr) {                                                        \
                    logger = spdlog::stdout_color_mt(logger_name);                              \
                }                                                                               \
                if (SPDLOG_ACTIVE_LEVEL > SPDLOG_LEVEL_DEBUG && logger != nullptr) {  \
                    logger->set_level(spdlog::level::debug);                                    \
                }                                                                               \
                return logger;                                                                  \
                }(static_class_name());                                                         \
            return _logger;                                                                     \
        }
#else
#define OHTOAI_DEFINE_CLASS(x)                                                                  \
    public:                                                                                     \
        virtual const char* class_name() const { return static_class_name(); }                  \
        static constexpr const char* static_class_name() { return (#x); }                       \
        static auto logger() {                                                                  \
            static auto _logger = [](const std::string& logger_name){                           \
                auto logger = spdlog::get(logger_name);                                         \
                if (logger == nullptr) {                                                        \
                    logger = spdlog::stdout_color_mt(logger_name);                              \
                }                                                                               \
                return logger;                                                                  \
                }(static_class_name());                                                         \
            return _logger;                                                                     \
        }
#endif

#define OHTOAI_CLIENT_REGISTER(x) \
    static ohtoai::ProductRegistrar<ohtoai::vnotice::client, x> x##_registrar(x::static_class_name());

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

        template <typename T = client>
        static auto create(const std::string& _class_name) {
            return std::dynamic_pointer_cast<T>(ohtoai::ProductFactory<client>::instance().product(_class_name));
        }

        static auto has(const std::string& _class_name) {
            return ohtoai::ProductFactory<client>::instance().hasProduct(_class_name);
        }

        static auto support_client_class_names() {
            return ohtoai::ProductFactory<client>::instance().getProductNames();
        }
    };
}
