cmake_minimum_required(VERSION 3.10)
project(test)

add_definitions(-DCATCH_CONFIG_MAIN)
enable_testing()

find_package(OpenSSL REQUIRED)
find_package(Threads REQUIRED)
add_subdirectory(${SOURCE_FOLDER}/client ${CMAKE_BINARY_DIR}/client)

# Add test files
file(GLOB test_files "*.test.cpp")
foreach (test_file ${test_files})
    set(SOURCES ${test_file})
    get_filename_component(test_name ${test_file} NAME_WLE)
    add_executable(${test_name} ${SOURCES})
    target_include_directories(${test_name} PRIVATE ${CMAKE_BINARY_DIR}/src/generated/inc)
    target_include_directories(${test_name} PRIVATE ${SOURCE_FOLDER}/inc)
    target_include_directories(${test_name} PRIVATE ${SOURCE_FOLDER})
    target_link_libraries (${test_name} PRIVATE Threads::Threads)
    target_link_libraries(${test_name} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
    target_link_libraries(${test_name} PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,client>")
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach ()
