cmake_minimum_required(VERSION 3.20)
project(BitArrayProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------
# Library
# --------------------------
add_library(BitArrayLib
    src/BitArray.cpp
    src/SpecialMethods.cpp
)

target_include_directories(BitArrayLib PUBLIC include)

# --------------------------
# Main executable
# --------------------------
add_executable(BitArrayApp
    src/main.cpp
)

target_link_libraries(BitArrayApp PRIVATE BitArrayLib)

# --------------------------
# GoogleTest
# --------------------------
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(BitArrayTests
    tests/BitArrayTests.cpp
)

target_link_libraries(BitArrayTests
    PRIVATE
    BitArrayLib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(BitArrayTests)