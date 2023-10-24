#pragma once
#include <nlohmann/json.hpp>

namespace ohtoai::vnotice
{
    struct message_template
    {
        std::string alias;
        std::string content;
        std::string type;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(message_template, alias, content, type)
    };
}
