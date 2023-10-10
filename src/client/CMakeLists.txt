cmake_minimum_required(VERSION 3.10)
include_guard(GLOBAL)
project(client)

aux_source_directory(${PROJECT_SOURCE_DIR} SRC_LIST)
add_library(${PROJECT_NAME} ${SRC_LIST})

target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto Threads::Threads)
target_include_directories(${PROJECT_NAME} PRIVATE ${SOURCE_FOLDER}/inc)
