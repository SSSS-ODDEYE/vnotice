cmake_minimum_required(VERSION 3.10)

# set the project name with the current directory name
get_filename_component(ProjectId ${CMAKE_SOURCE_DIR} NAME_WE)
string(REPLACE " " "_" ProjectId ${ProjectId})

# set the project name and version
project(${ProjectId})

if(WIN32)
    set(WINDOWS TRUE)
elseif(APPLE)
    set(MACOS TRUE)
elseif(UNIX)
    set(LINUX TRUE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set(SOURCE_FOLDER ${PROJECT_SOURCE_DIR}/src)
if(WINDOWS)
    set(OPENSSL_ROOT_DIR "C:/Program Files/OpenSSL" CACHE STRING "openssl root" FORCE)
endif(WINDOWS)

# include top level include directory
include_directories(${PROJECT_SOURCE_DIR}/inc)

# set the output directory for the build executables and libraries
add_subdirectory(src)
add_subdirectory(test)
