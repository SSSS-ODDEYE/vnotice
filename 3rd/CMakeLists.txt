include(FetchContent)

set(INJA_USE_EMBEDDED_JSON OFF CACHE BOOL "Use inja embedded json library" FORCE)
set(INJA_BUILD_TESTS OFF CACHE BOOL "Build inja tests" FORCE)
set(BUILD_BENCHMARK OFF CACHE BOOL "Build benchmark" FORCE)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG         v3.11.2
)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse
    GIT_TAG         v2.9
)
FetchContent_Declare(
    tabulate
    GIT_REPOSITORY https://github.com/p-ranav/tabulate
    GIT_TAG         v1.5
)
FetchContent_Declare(
    scnlib
    GIT_REPOSITORY https://github.com/eliaskosunen/scnlib
    GIT_TAG         v1.1.2
)
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG         v1.12.0
)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2
    GIT_TAG         v3.4.0
)
FetchContent_Declare(
    inja
    GIT_REPOSITORY https://github.com/pantor/inja
    GIT_TAG         v3.4.0
)
FetchContent_Declare(
    cpp-httplib
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
    GIT_TAG         v0.14.1
)

FetchContent_MakeAvailable(nlohmann_json)
FetchContent_MakeAvailable(argparse)
FetchContent_MakeAvailable(tabulate)
FetchContent_MakeAvailable(scnlib)
FetchContent_MakeAvailable(spdlog)
FetchContent_MakeAvailable(Catch2)
FetchContent_MakeAvailable(cpp-httplib)
FetchContent_MakeAvailable(inja)
