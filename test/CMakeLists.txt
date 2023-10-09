cmake_minimum_required(VERSION 3.10)
project(test)

set(CMAKE_CXX_STANDARD 17)
add_definitions(-DCATCH_CONFIG_MAIN)
enable_testing()

if(WIN32)
    set(WINDOWS TRUE)
elseif(APPLE)
    set(MACOS TRUE)
elseif(UNIX)
    set(LINUX TRUE)
endif()

if(WINDOWS)
    set(OPENSSL_ROOT_DIR "C:/Program Files/OpenSSL" CACHE STRING "openssl root" FORCE)
endif(WINDOWS)
find_package(OpenSSL REQUIRED)
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

    target_include_directories(${test_name} PRIVATE ${CMAKE_BINARY_DIR}/src/generated/inc)
    target_include_directories(${test_name} PRIVATE ../src/inc)
    target_include_directories(${test_name} PRIVATE ../src)
    target_link_libraries (${test_name} PRIVATE Threads::Threads)
    target_link_libraries(${test_name} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach ()
