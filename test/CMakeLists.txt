cmake_minimum_required(VERSION 3.10)
project(test)

include_directories(${CMAKE_BINARY_DIR}/src/generated/inc)
add_definitions(-DCATCH_CONFIG_MAIN)
enable_testing()

find_package(Threads REQUIRED)

# Add test files
file(GLOB test_files "*.test.cpp")
foreach (test_file ${test_files})
    set(SOURCES
        ${test_file}
        ../src/client/http_robot_client.cpp
        ../src/client/feishu_client.cpp
        ../src/client/qywechat_client.cpp
    )
    get_filename_component(test_name ${test_file} NAME_WLE)
    add_executable(${test_name} ${SOURCES})
    add_test(NAME ${test_name} COMMAND ${test_name})
    target_link_libraries (${test_name} Threads::Threads)
endforeach ()
