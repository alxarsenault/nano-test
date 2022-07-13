cmake_minimum_required(VERSION 3.22.0)

# No reason to set CMAKE_CONFIGURATION_TYPES if it's not a multiconfig generator.
get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if (IS_MULTI_CONFIG)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "" FORCE)
    set(CMAKE_XCODE_GENERATE_SCHEME ON)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
else()
    if (NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE "Release"  CACHE STRING "Build type" FORCE)
    endif()
endif()

project(nano-test VERSION 1.0.0 LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

option(NANO_TEST_BUILD_EXAMPLES "Build examples." OFF)
option(NANO_TEST_DEV "Development build" OFF)

# nano-test interface.
set(NANO_TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/nano/utest.h")
add_library(${PROJECT_NAME} INTERFACE ${NANO_TEST_SOURCES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${NANO_TEST_SOURCES})
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
add_library(nano::test ALIAS ${PROJECT_NAME})

if (NANO_TEST_DEV)
    set(NANO_TEST_BUILD_EXAMPLES ON)
endif()

if (NANO_TEST_DEV)
    find_program(CLANG_FORMAT clang-format REQUIRED)
    add_custom_target(check-nano-test-formatting DEPENDS ${NANO_TEST_SOURCES})
    add_custom_command(TARGET check-nano-test-formatting PRE_BUILD
        COMMAND "${CLANG_FORMAT}" --Werror  --dry-run ${NANO_TEST_SOURCES}
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
    add_dependencies(${PROJECT_NAME} check-nano-test-formatting)
endif()

# Examples.
if (NANO_TEST_BUILD_EXAMPLES)
    function(nano_add_example PNAME PPATH)
        file(GLOB_RECURSE EXAMPLE_SOURCE_FILES "${PPATH}/*.cpp"  "${PPATH}/*.h")
        source_group(TREE ${PPATH} FILES ${EXAMPLE_SOURCE_FILES})

        add_executable(${PNAME} ${EXAMPLE_SOURCE_FILES})
        target_include_directories(${PNAME} PUBLIC ${PPATH})
        target_link_libraries(${PNAME} PUBLIC nano-test)

        set(CLANG_OPTIONS -Weverything -Wno-c++98-compat)
        set(MSVC_OPTIONS /W4)

        target_compile_options(${PNAME} PUBLIC
            "$<$<CXX_COMPILER_ID:Clang,AppleClang>:${CLANG_OPTIONS}>"
            "$<$<CXX_COMPILER_ID:MSVC>:${MSVC_OPTIONS}>"
        )
    endfunction()

    set(NANO_TEST_EXAMPLES assert basic range output test)
    set(NANO_TEST_EXAMPLES_PROJECTS "")

    set(NANO_EX_CMD "")
    foreach(EXAMPLE ${NANO_TEST_EXAMPLES})
        set(PNAME nano-test-${EXAMPLE})
        nano_add_example(${PNAME} ${CMAKE_CURRENT_SOURCE_DIR}/examples/${EXAMPLE})
        list(APPEND NANO_TEST_EXAMPLES_PROJECTS "${PNAME}")
        list(APPEND NANO_EX_CMD COMMAND $<TARGET_FILE:${PNAME}>)
    endforeach()

    add_custom_target(run-${PROJECT_NAME}
        DEPENDS ${NANO_TEST_EXAMPLES_PROJECTS}
        ${NANO_EX_CMD}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    )
endif()
