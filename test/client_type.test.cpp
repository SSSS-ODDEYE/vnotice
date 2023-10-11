#include <catch2/catch.hpp>
#include "client/client.h"

TEST_CASE("Verify all excepted client types are self-registered") {
    std::vector<std::string> excepted_client_names = {"http_client", "qywechat_client", "feishu_client"};
    auto client_names = ohtoai::vnotice::client::support_client_class_names();

    REQUIRE(client_names.size() == excepted_client_names.size());
    for (auto excepted_client_name : excepted_client_names) {
        bool found = false;
        for (auto client_name : client_names) {
            if (excepted_client_name == client_name) {
                found = true;
                break;
            }
        }
        REQUIRE(found);
    }
}

TEST_CASE("Verify client can be created by class name") {
    auto client_names = ohtoai::vnotice::client::support_client_class_names();
    for (auto client_name : client_names) {
        auto client = ohtoai::vnotice::client::create(client_name);
        REQUIRE(client != nullptr);
        REQUIRE(client->class_name() == client_name);
    }
}

TEST_CASE("Verify non-exist client cannot be created") {
    auto client = ohtoai::vnotice::client::create("non-exist-client@#$%^&*()");
    REQUIRE(client == nullptr);
}
