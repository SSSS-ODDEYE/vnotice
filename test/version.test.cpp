#include <catch2/catch.hpp>
#include <version.h>

TEST_CASE("Version info not empty", "[single-file]" ) {
    REQUIRE(VersionHelper::getInstance().AppName != "");
    REQUIRE(VersionHelper::getInstance().Author != "");
    REQUIRE(VersionHelper::getInstance().Email != "");
    REQUIRE(VersionHelper::getInstance().Description != "");
    REQUIRE(VersionHelper::getInstance().Version != "");
    REQUIRE(VersionHelper::getInstance().CommitHash != "");
    REQUIRE(VersionHelper::getInstance().CommitDate != "");
    REQUIRE(VersionHelper::getInstance().BuildDate != "");
    REQUIRE(VersionHelper::getInstance().BuildTime != "");
}
