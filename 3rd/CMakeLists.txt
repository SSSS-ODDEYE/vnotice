include(FetchContent)

set(INJA_USE_EMBEDDED_JSON OFF CACHE BOOL "Use inja embedded json library" FORCE)
set(INJA_BUILD_TESTS OFF CACHE BOOL "Build inja tests" FORCE)
set(BUILD_BENCHMARK OFF CACHE BOOL "Build benchmark" FORCE)

FetchContent_Declare(
    nlohmann_json
    URL             https://github.com/nlohmann/json/archive/v3.11.2.tar.gz
    # GIT_REPOSITORY https://github.com/nlohmann/json
    # GIT_TAG         v3.11.2
)
FetchContent_Declare(
    argparse
    URL             https://github.com/p-ranav/argparse/archive/v2.9.tar.gz
    # GIT_REPOSITORY https://github.com/p-ranav/argparse
    # GIT_TAG         v2.9
)
FetchContent_Declare(
    tabulate
    URL             https://github.com/p-ranav/tabulate/archive/v1.5.tar.gz
    # GIT_REPOSITORY https://github.com/p-ranav/tabulate
    # GIT_TAG         v1.5
)
FetchContent_Declare(
    scnlib
    URL             https://github.com/eliaskosunen/scnlib/archive/v1.1.2.tar.gz
    # GIT_REPOSITORY https://github.com/eliaskosunen/scnlib
    # GIT_TAG         v1.1.2
)
FetchContent_Declare(
    spdlog
    URL             https://github.com/gabime/spdlog/archive/v1.12.0.tar.gz
    # GIT_REPOSITORY https://github.com/gabime/spdlog
    # GIT_TAG         v1.12.0
)
FetchContent_Declare(
    Catch2
    URL             https://github.com/catchorg/Catch2/archive/v3.4.0.tar.gz
    # GIT_REPOSITORY https://github.com/catchorg/Catch2
    # GIT_TAG         v3.4.0
)
FetchContent_Declare(
    inja
    URL             https://github.com/pantor/inja/archive/v3.4.0.tar.gz
    # GIT_REPOSITORY https://github.com/pantor/inja
    # GIT_TAG         v3.4.0
)
FetchContent_Declare(
    cpp-httplib
    URL             https://github.com/yhirose/cpp-httplib/archive/v0.14.1.tar.gz
    # GIT_REPOSITORY https://github.com/yhirose/cpp-httplib
    # GIT_TAG         v0.14.1
)
FetchContent_Declare(
    eventpp
    URL             https://github.com/wqking/eventpp/archive/v0.1.3.tar.gz
    # GIT_REPOSITORY https://github.com/wqking/eventpp
    # GIT_TAG         v0.1.3
)
FetchContent_Declare(
    yaml-cpp
    URL             https://github.com/jbeder/yaml-cpp/archive/0.8.0.tar.gz
    # GIT_REPOSITORY https://github.com/jbeder/yaml-cpp
    # GIT_TAG         0.8.0
)

FetchContent_Declare(
    factory_method
    # URL             https://gist.github.com/ohto-ai/2165091d8f934b0852eb12d9224b0e6a/archive/b60a166d393d8fb22f4978a7cb2018c91d5cb414.zip
    GIT_REPOSITORY https://gist.github.com/2165091d8f934b0852eb12d9224b0e6a.git
    SOURCE_DIR ../inc
)

FetchContent_MakeAvailable(nlohmann_json argparse tabulate scnlib spdlog Catch2 cpp-httplib inja eventpp yaml-cpp factory_method)
