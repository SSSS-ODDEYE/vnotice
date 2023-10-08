#include <argparse/argparse.hpp>
#include <spdlog/fmt/fmt.h>
#include <version.h>
#include "client/client.h"

TEST_CASE("Client type is correct", "[single-file]" ) {
    for (auto robot_name : {"http_robot_client", "feishu_client", "qywechat_client"}) {
        auto robot = ohtoai::vnotice::client_factory::instance().product(robot_name);
        REQUIRE(robot != nullptr);
        REQUIRE(robot->class_name() == robot_name);
    }
}
