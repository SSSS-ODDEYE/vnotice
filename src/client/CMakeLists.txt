cmake_minimum_required(VERSION 3.10)
include_guard(GLOBAL)
project(${ProjectId}_client)

aux_source_directory(${PROJECT_SOURCE_DIR} SRC_LIST)
add_library(${PROJECT_NAME} ${SRC_LIST})

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
if(CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(${PROJECT_NAME} PRIVATE SPDLOG_ACTIVE_LEVEL=SPDLOG_LEVEL_DEBUG)
endif()

if(OPENSSL_FOUND)
    target_compile_definitions(${PROJECT_NAME} PRIVATE CPPHTTPLIB_OPENSSL_SUPPORT)
endif(OPENSSL_FOUND)
target_link_libraries(${PROJECT_NAME} PRIVATE
            Threads::Threads
            $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::SSL>
            $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::Crypto>
            nlohmann_json
            inja
            httplib
            argparse
            spdlog $<$<BOOL:${MINGW}>:ws2_32>)
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_FOLDER}/inc)
