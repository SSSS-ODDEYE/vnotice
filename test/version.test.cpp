#include <version.h>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Version info not empty", "[single-file]" ) {
    REQUIRE(VersionHelper::getInstance().AppName != "");
    REQUIRE(VersionHelper::getInstance().Author != "");
    REQUIRE(VersionHelper::getInstance().Email != "");
    REQUIRE(VersionHelper::getInstance().Description != "");
    REQUIRE(VersionHelper::getInstance().Version != "");
    REQUIRE(VersionHelper::getInstance().GitDescribe != "");
    REQUIRE(VersionHelper::getInstance().GitSha1 != "");
    REQUIRE(VersionHelper::getInstance().GitRefSpec != "");
    REQUIRE(VersionHelper::getInstance().BuildDate != "");
    REQUIRE(VersionHelper::getInstance().BuildTime != "");
}
