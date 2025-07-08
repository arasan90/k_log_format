cmake_minimum_required(VERSION 3.10)
include(GoogleTest)

project(k_log_format_test LANGUAGES C CXX VERSION 1.0.0)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/k_log_format_test.cpp)
target_link_libraries(${PROJECT_NAME} gtest gtest_main k_log_format)

gtest_discover_tests(${PROJECT_NAME})
