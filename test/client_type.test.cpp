#include <catch2/catch.hpp>
#include "client/client.h"

TEST_CASE("Client type is correct", "[single-file]" ) {
    std::string robot_list[] = {"http_robot_client", "feishu_client", "qywechat_client"};
    for (auto robot_name : robot_list) {
        auto robot = ohtoai::vnotice::client_factory::instance().product(robot_name);
        REQUIRE(robot != nullptr);
        REQUIRE(robot->class_name() == robot_name);
    }
}
