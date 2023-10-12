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

    argparse::ArgumentParser send_command("send", "", argparse::default_arguments::help);
    send_command.add_description("Send message to robot");
    send_command.add_argument("-R", "--robot")
                .help("Specify the robot");
    send_command.add_argument("-M", "--message")
                .help("Specify the message");

    argparse::ArgumentParser robot_command("robot", "", argparse::default_arguments::help);
    robot_command.add_description("Manage robot");
    argparse::ArgumentParser robot_list_command("list", "", argparse::default_arguments::help);
    robot_list_command.add_description("List all robots");
    argparse::ArgumentParser robot_remove_command("remove", "", argparse::default_arguments::help);
    robot_remove_command.add_description("Remove a robot");
    argparse::ArgumentParser robot_update_command("update", "", argparse::default_arguments::help);
    robot_update_command.add_description("Update a robot");

    robot_command.add_subparser(robot_list_command);
    robot_command.add_subparser(robot_remove_command);
    robot_command.add_subparser(robot_update_command);

    argparse::ArgumentParser configure_command("config", "", argparse::default_arguments::help);
    configure_command.add_description("Configure");
    argparse::ArgumentParser configure_robot_command("robot", "", argparse::default_arguments::help);
    configure_robot_command.add_description("Configure robot");
    argparse::ArgumentParser configure_message_command("message", "", argparse::default_arguments::help);
    configure_message_command.add_description("Configure message");

    configure_command.add_subparser(configure_robot_command);
    configure_command.add_subparser(configure_message_command);

    program.add_subparser(send_command);
    program.add_subparser(robot_command);
    program.add_subparser(configure_command);

    try {
        program.parse_args(argc, argv);
    }
    catch (const std::exception &e) {
        fmt::print(stderr, "Exception occur when call `parse_args` ({})\n", e.what());
        std::exit(1);
    }

    auto names = ohtoai::vnotice::client::support_client_class_names();
    fmt::print("clients = {}\n", fmt::join(names, ", "));

    auto robot = ohtoai::vnotice::client::create("feishu_client");
    if (robot == nullptr) {
        fmt::print(stderr, "Robot type not found\n");
        std::exit(1);
    }

    fmt::print("robot.class_name = {}\n", robot->class_name());
    robot->send({}, {}, {});
    return 0;
}
