set(GIT_COMMIT_HASH "")
set(GIT_COMMIT_DATE "")
set(BUILD_VERSION "")
set(IS_DEV_VERSION true)
set(BUILD_VERSION_MAJOR "0")
set(BUILD_VERSION_MINOR "0")
set(BUILD_VERSION_PATCH "0")

find_package(Git QUIET)
if(GIT_FOUND)
    # Get the current Git hash
    execute_process(
        COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%h
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )
    # Get latest commit date
    execute_process(
        COMMAND ${GIT_EXECUTABLE} log -1 --format=%cd --date=short
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_DATE
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )

    # Check if the latest tag is the current commit
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --tags --exact-match HEAD
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        RESULT_VARIABLE GIT_CHECK_COMMIT_IN_TAGS
        OUTPUT_VARIABLE GIT_LATEST_TAG
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )

    if (${GIT_CHECK_COMMIT_IN_TAGS} EQUAL 0)
        # If the latest tag is the current commit, set BUILD_VERSION to the tag name
        # Parse the tag name to get the version components
        string(REGEX MATCH "v([0-9]+)\\.([0-9]+)\\.([0-9]+)" VERSION_REGEX ${GIT_LATEST_TAG})
        if(VERSION_REGEX)
            set(BUILD_VERSION_MAJOR ${CMAKE_MATCH_1})
            set(BUILD_VERSION_MINOR ${CMAKE_MATCH_2})
            set(BUILD_VERSION_PATCH ${CMAKE_MATCH_3})
            set(BUILD_VERSION ${GIT_LATEST_TAG})
            set(IS_DEV_VERSION false)
            message(STATUS "Build version: ${BUILD_VERSION}(${GIT_COMMIT_HASH})")
        else()
            message(WARNING "Invalid tag name format: ${GIT_LATEST_TAG}")
            set(BUILD_VERSION ${GIT_COMMIT_HASH})
            set(BUILD_VERSION_MAJOR "0")
            set(BUILD_VERSION_MINOR "0")
            set(BUILD_VERSION_PATCH "0")
            set(IS_DEV_VERSION true)
            message(STATUS "Build version: ${BUILD_VERSION}")
        endif()
    else()
        # If the latest tag is not the current commit, set BUILD_VERSION to the commit hash
        set(BUILD_VERSION ${GIT_COMMIT_HASH})
        set(BUILD_VERSION_MAJOR "0")
        set(BUILD_VERSION_MINOR "0")
        set(BUILD_VERSION_PATCH "0")
        set(IS_DEV_VERSION true)
        message(STATUS "Build version: ${BUILD_VERSION}")
    endif()
endif()
