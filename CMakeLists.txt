cmake_minimum_required(VERSION 3.10)

# set the project name with the current directory name
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME_WE)
string(REPLACE " " "_" ProjectId ${ProjectId})

# set the project name and version
project(${ProjectId})

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

# include top level include directory
include_directories(${PROJECT_SOURCE_DIR}/inc)

# set the output directory for the build executables and libraries
add_subdirectory(src)
add_subdirectory(test)
