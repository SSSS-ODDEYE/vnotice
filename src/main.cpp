#include <argparse/argparse.hpp>
#include <spdlog/fmt/fmt.h>
#include <version.h>
#include "client/client.h"

/**
 * config
 *      robot
 *          id xxxx-xxx-xxx-xx
 *          alias
 *          type qywechat/feishu
 *      message_template
 *          type qywechat/feishu
 *          
 *      default robot id/alias
 * 
*/

int main(int argc, char **argv)
{
    argparse::ArgumentParser program(VersionHelper::getInstance().AppName, VersionHelper::getInstance().Version);

    program.add_description(VersionHelper::getInstance().Description);
    program.add_epilog(fmt::format("Author: {} <{}>\nSite: {}", VersionHelper::getInstance().Author, VersionHelper::getInstance().Email, VersionHelper::getInstance().Homepage));
    program.add_argument("-R", "--robot")
            .help("Specify the robot")
            .action([](const std::string &value) { std::cout << "Robot name: " << value << std::endl; });

    try
    {
        program.parse_args(argc, argv);
    }
    catch (const std::exception &e)
    {
        fmt::print(stderr, "{}\n", e.what());
        std::exit(1);
    }

    auto robot = ohtoai::vnotice::client_factory::instance().product("qywechat");

    if (robot == nullptr)
    {
        fmt::print(stderr, "Robot type not found\n");
        std::exit(1);
    }
    robot->send(ohtoai::vnotice::robot{"", "", ""}, ohtoai::vnotice::message_template{"", ""}, nlohmann::json{});

    std::cout << "Hello, World!" << std::endl;
    return 0;
}
