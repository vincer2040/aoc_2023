cmake_minimum_required(VERSION 3.11)

project(aoc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Werror -pedantic -fstack-clash-protection \
-fstack-protector-all -fstack-protector-strong -Werror=format-security -O2")

set(CMAKE_CXX_FLAGS_RELEASE "-Wall -Werror -pedantic -fstack-clash-protection -fstack-protector-all \
-fstack-protector-strong -Werror=format-security -pipe -O2 -s -DNDEBUG")

enable_testing()
add_subdirectory(tests)

add_library(
    helpers
    src/reader.cc
    src/str_helpers.cc
)

add_library(
    day1
    src/day1.cc
)

add_library(
    day2
    src/day2.cc
)

add_library(
    day3
    src/day3.cc
)

add_library(
    day4
    src/day4.cc
)

add_library(
    day6
    src/day6.cc
)

add_library(
    day7
    src/day7.cc
)

add_library(
    day8
    src/day8.cc
)

add_library(
    day9
    src/day9.cc
)

add_library(
    day11
    src/day11.cc
)

add_executable(
    aoc
    src/main.cc
)

target_link_libraries(day1 helpers)
target_link_libraries(day2 helpers)
target_link_libraries(day3 helpers)
target_link_libraries(day4 helpers m)
target_link_libraries(day6 helpers m)
target_link_libraries(day8 helpers)
target_link_libraries(day9 helpers)
target_link_libraries(day11 helpers m)
target_link_libraries(
    aoc
    day1
    day2
    day3
    day4
    day6
    day7
    day8
    day9
    day11
)

