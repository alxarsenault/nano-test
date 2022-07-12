# utest

## Supported Platforms

nano-test requires a codebase and compiler compliant with the C++98 standard or newer.

The following platforms and compilers are officially supported.
If you notice any problems on your platform, please file an issue.
Pull requests containing fixes are welcome!

#### Operating systems
* Linux
* macOS
* Windows

#### Compilers
* gcc 10+
* clang 10+
* MSVC 2019+

## Set up a project

CMake uses a file named CMakeLists.txt to configure the build system for a project.
You’ll use this file to set up your project and declare a dependency on nano-test.

First, create a directory for your project:

```bash
$ mkdir -p unit_tests/src && cd unit_tests
```

Next, you’ll create the CMakeLists.txt file and declare a dependency on nano-test. There are many ways to express dependencies in the CMake ecosystem; in this quickstart, you’ll use the FetchContent CMake module. To do this, in your project directory, create a file named CMakeLists.txt (`unit_tests/CMakeLists.txt`) with the following contents:

```cmake
cmake_minimum_required(VERSION 3.22)
project(UnitTests)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  nano-test
  GIT_REPOSITORY https://github.com/Meta-Sonic/nano-test.git
  GIT_TAG master
)

FetchContent_MakeAvailable(nano-test)

file(GLOB_RECURSE UNIT_TESTS_SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(${PROJECT_NAME} ${UNIT_TESTS_SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(${PROJECT_NAME} PUBLIC nano-test)
```

As an example, create a file named main.cpp in your `unit_tests/src/` directory with the following contents:

```cpp
#include "nano/utest.h"

namespace {
TEST_CASE("Template", Template, "Template test case description") {
    EXPECT_EQ(1, 1);
    EXPECT_NE(0, 1);
}
} // namespace.

NANO_TEST_MAIN()
```

Now you can build and run your test:

```bash
cmake -S . -B build
cmake --build build
./build/UnitTests 
```

```terminal
[==========] Running 1 test from 1 test group.

[----------] 1 test from group 'Template'
[ RUN      ] > test case Template : Template test case description
[       OK ] < test case Template (2 checks) (4 us)
[----------] group 'Template' (14 us). 

[==========] 1 test from 1 test group (21 us).
[  PASSED  ] 1 test
```
Congratulations! You’ve successfully built and run a test binary using nano-test.


## Assertions

```cpp
TEST_CASE("GroupOne", FooA, "Foo A description")
{
    EXPECT_EQ(1, 1);
}

TEST_CASE("GroupOne", FooB)
{
    EXPECT_EQ(1, 1);
}
```


```cpp
TEST_CASE("GroupOne", FooB)
{
  int a = 0;
  EXPECT_NOT_NULL(&a);
  EXPECT_NULL(nullptr);

  // A == B
  EXPECT_EQ(1, 1);
  
  // A != B
  EXPECT_NE(0, 1);

  // A < B
  EXPECT_LT(5, 6);

  // A <= B
  EXPECT_LE(5, 6);

  // A > B
  EXPECT_GT(7, 6);
  
  // A >= B
  EXPECT_GE(7, 6);

  // std::string(A) == std::string(B)
  EXPECT_STR_EQ("A", "A");
  
  // std::string(A) != std::string(B)
  EXPECT_STR_NE("A", "B");

  // A == B
  EXPECT_FLOAT_EQ(2.2f, 2.2f);
  
  // A == B
  EXPECT_FLOAT_EQ(2.2000001f, 2.2f);

  // A != B
  EXPECT_FLOAT_NE(2.2f, 2.3f);

  // A == B
  EXPECT_FLOAT_EQ_T(4.5f, 4.5f, 0.1f);

  // A == B
  EXPECT_FLOAT_NE_T(4.5f, 4.7f, 0.01f);}
```
