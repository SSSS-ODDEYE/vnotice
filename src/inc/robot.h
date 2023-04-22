#pragma once
#include <nlohmann/json.hpp>

namespace ohtoai::vnotice
{
    struct robot
    {
        std::string alias;
        std::string id;
        std::string type;
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(robot, alias, id, type)
    };
}
