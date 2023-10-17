include(FetchContent)

set(INJA_USE_EMBEDDED_JSON OFF CACHE BOOL "Use inja embedded json library" FORCE)
set(INJA_BUILD_TESTS OFF CACHE BOOL "Build inja tests" FORCE)
set(BUILD_BENCHMARK OFF CACHE BOOL "Build benchmark" FORCE)

function(add_3rd_repo repo_name git_repo git_tag)
    if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${repo_name}/CMakeLists.txt)
        message(STATUS "Fetching ${repo_name} from ${git_repo}...")
        # if git_tag not empty
        if (NOT "${git_tag}" STREQUAL "")
            FetchContent_Declare(
                ${repo_name}
                GIT_REPOSITORY ${git_repo}
                GIT_TAG ${git_tag}
            )
        else()
            FetchContent_Declare(
                ${repo_name}
                GIT_REPOSITORY ${git_repo}
            )
        endif()
    else()
        message(STATUS "Found ${repo_name} in ${CMAKE_CURRENT_SOURCE_DIR}/${repo_name}")
        FetchContent_Declare(
            ${repo_name}
            SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${repo_name}
        )
    endif()
    FetchContent_MakeAvailable(${repo_name})
endfunction()

add_3rd_repo(nlohmann_json "https://github.com/nlohmann/json" v3.11.2)
add_3rd_repo(argparse "https://github.com/p-ranav/argparse" v2.9)
add_3rd_repo(tabulate "https://github.com/p-ranav/tabulate" v1.5)
add_3rd_repo(scnlib "https://github.com/eliaskosunen/scnlib" v1.1.2)
add_3rd_repo(spdlog "https://github.com/gabime/spdlog" v1.12.0)
add_3rd_repo(Catch2 "https://github.com/catchorg/Catch2" v3.4.0)
add_3rd_repo(inja "https://github.com/pantor/inja" v3.4.0)
add_3rd_repo(cpp-httplib "https://github.com/yhirose/cpp-httplib" v0.14.1)
add_3rd_repo(eventpp "https://github.com/wqking/eventpp" v0.1.3)
add_3rd_repo(yaml-cpp "https://github.com/jbeder/yaml-cpp" 0.8.0)
