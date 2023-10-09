cmake_minimum_required(VERSION 3.10)

# set version from git tag
include(../cmake/version_from_git_tag.cmake)

# set the project name and version
project(${ProjectId} LANGUAGES CXX VERSION ${BUILD_VERSION_MAJOR}.${BUILD_VERSION_MINOR}.${BUILD_VERSION_PATCH})

# set project maintainer and contact
set(PROJECT_MAINTAINER "OhtoAi")
set(PROJECT_CONTACT "zhu.thatboy@outlook.com")
set(PROJECT_DESCRIPTION "企业微信/飞书机器人消息推送工具")
set(PROJECT_DEBIAN_DEPENDENCIES)
set(PROJECT_HOMEPAGE "https://github.com/SSSS-ODDEYE/vnotice/")

# trans project name
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_VAR)
string(REPLACE "-" "_" PROJECT_NAME_VAR ${PROJECT_NAME_VAR})

# platform specific settings
if(WINDOWS)
    set(BINARY_PATH "bin/${PROJECT_NAME}.exe")
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    add_definitions(-DNOMINMAX)
else()
    set(BINARY_PATH "bin/${PROJECT_NAME}")
endif()

# configure .in file
configure_file(
    inc/version.h.in
    generated/inc/version.h
)

# Add source files
set(SOURCES
    main.cpp
)

add_subdirectory(client)
# Build the executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Add include directories
target_include_directories(${PROJECT_NAME} PRIVATE inc)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR}/generated/inc)

find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)
target_link_libraries(${PROJECT_NAME} PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,client>")

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

# set install target
if (LINUX OR WINDOWS)
    include(../cmake/package.cmake)
endif()
