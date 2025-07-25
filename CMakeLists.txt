cmake_minimum_required(VERSION 3.10)

if(K_LOG_DEV)
    project(k_log_format LANGUAGES C VERSION 1.0.0)

    include(${CMAKE_CURRENT_LIST_DIR}/k_log_format.cmake)
    include(FetchContent)
        FetchContent_Declare(
            gtest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.16.0
        )

    set(k_log_format_sources)
    set(k_log_format_public_include_dirs)
    k_log_format_get_sources(k_log_format_sources)
    k_log_format_get_public_headers(k_log_format_public_include_dirs)

    add_library(${PROJECT_NAME} STATIC ${k_log_format_sources})
    target_include_directories(${PROJECT_NAME} PUBLIC ${k_log_format_public_include_dirs})

    SET(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -coverage -fprofile-arcs -ftest-coverage")
    SET(GCC_COVERAGE_LINK_FLAGS "-coverage -lgcov")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror ${GCC_COVERAGE_COMPILE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

    FetchContent_MakeAvailable(gtest)
    enable_testing()
    include(CTest)

    add_subdirectory(test)

    k_log_format_create_mock_library()
else()
    message(FATAL_ERROR "This cmake file is only for development purposes. Please use the main CMakeLists.txt file for building the library.")

endif()