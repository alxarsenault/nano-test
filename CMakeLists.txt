cmake_minimum_required(VERSION 3.22.0)
project(utest VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(UTEST_BUILD_EXAMPLES "Build examples." ON)

# utest interface.
set(UTEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/utest.h")
add_library(${PROJECT_NAME} INTERFACE ${UTEST_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${UTEST_SOURCES})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


# Examples.
if (UTEST_BUILD_EXAMPLES)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
endif()