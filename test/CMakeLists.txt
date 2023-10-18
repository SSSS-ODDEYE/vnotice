cmake_minimum_required(VERSION 3.24)
project(test)

enable_testing()

add_custom_target(${PROJECT_NAME} EXCLUDE_FROM_ALL)

# Add test files
file(GLOB test_files "*.test.cpp")
foreach (test_file ${test_files})
    set(SOURCES ${test_file})
    get_filename_component(test_name ${test_file} NAME_WLE)
    add_executable(${test_name} EXCLUDE_FROM_ALL ${SOURCES})
    target_compile_definitions(${test_name} PRIVATE CATCH_CONFIG_MAIN)
    target_link_libraries(${test_name} PRIVATE
        "$<LINK_LIBRARY:WHOLE_ARCHIVE,${ProjectId}::client>"
        Catch2 Catch2WithMain
        Threads::Threads
        $<$<BOOL:${OpenSSL_FOUND}>:OpenSSL::SSL>
        $<$<BOOL:${OpenSSL_FOUND}>:OpenSSL::Crypto>
        nlohmann_json
        inja
        httplib
        argparse
        spdlog $<$<BOOL:${MINGW}>:ws2_32>)
    add_test(NAME ${test_name} COMMAND ${test_name})
    add_dependencies(${PROJECT_NAME} ${test_name})
    list(APPEND test_list ${test_name})
endforeach ()

if(GENERATE_CODE_COVERAGE AND LINUX AND CMAKE_BUILD_TYPE MATCHES Debug)
    setup_target_for_coverage_lcov(NAME coverage
        EXECUTABLE ctest --build-config Debug --output-on-failure
        BASE_DIRECTORY ${SOURCE_FOLDER}
        EXCLUDE "/usr/*" "${CMAKE_SOURCE_DIR}/inc/*" "${CMAKE_SOURCE_DIR}/test/*" "${CMAKE_SOURCE_DIR}/build/*" "${CMAKE_SOURCE_DIR}/3rd/*"
        DEPENDENCIES ${test_list})
endif(GENERATE_CODE_COVERAGE AND LINUX AND CMAKE_BUILD_TYPE MATCHES Debug)
