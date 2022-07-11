cmake_minimum_required(VERSION 3.22.0)
project(nano-test VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(NANO_TEST_BUILD_EXAMPLES "Build examples." OFF)

# nano-test interface.
set(NANO_TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/nano/utest.h")
add_library(${PROJECT_NAME} INTERFACE ${NANO_TEST_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${NANO_TEST_SOURCES})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


# Examples.
if (NANO_TEST_BUILD_EXAMPLES)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
endif()
