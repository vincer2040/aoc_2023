cmake_minimum_required(VERSION 3.10)

project(c VERSION 0.1)

enable_testing()

add_subdirectory(tests)
set(INSTALL_PREFIX "/usr/local")

set(CMAKE_C_COMPILER "gcc")

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=c99 -Wall -Werror -pedantic -fstack-clash-protection -fstack-protector-all -fstack-protector-strong -Werror=format-security -Werror=implicit-function-declaration -pipe -O2")

set(CMAKE_C_FLAGS_RELEASE "-std=c99 -Wall -Werror -pedantic -fstack-clash-protection -fstack-protector-all -fstack-protector-strong -Werror=format-security -Werror=implicit-function-declaration -pipe -O2 -s -DNDEBUG")

add_library(
    helpers
    src/reader.c
    src/line_iter.c
    src/vec.c
    src/ht.c
    src/util.c
    src/sha256.c
    src/siphash.c
)

add_library(
    day1
    src/day1.c
)

add_library(
    day2
    src/day2.c
)

add_library(
    day3
    src/day3.c
)

add_library(
    day4
    src/day4.c
)

add_library(
    day5
    src/day5.c
)

add_library(
    day6
    src/day6.c
)

add_executable(
    aoc
    src/aoc.c
)

target_link_libraries(day1 helpers)
target_link_libraries(day2 helpers)
target_link_libraries(day3 helpers)
target_link_libraries(day4 helpers m)
target_link_libraries(day5 helpers)
target_link_libraries(day6 helpers m)

target_link_libraries(
    aoc
    day1
    day2
    day3
    day4
    day5
    day6
)
