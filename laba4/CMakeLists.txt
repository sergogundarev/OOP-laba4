cmake_minimum_required(VERSION 3.15)
project(laba4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9fdab60b14b31b89d3e8dce.zip
)
FetchContent_MakeAvailable(googletest)


add_executable(figure_main main.cpp)


add_executable(figure_test test.cpp)
target_link_libraries(figure_test gtest_main gmock)


if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(figures_main PRIVATE "-std=c++17")
    target_compile_options(figures_tests PRIVATE "-std=c++17")
endif()