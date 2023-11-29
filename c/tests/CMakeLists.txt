include(FetchContent)

set(LIBCHECK_VERSION "0.15.2")

# Use FetchContent to download and include libcheck
FetchContent_Declare(
    libcheck
    URL https://github.com/libcheck/check/archive/${LIBCHECK_VERSION}.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP true  # Specify the option here
)

FetchContent_MakeAvailable(libcheck)
add_executable(
    aoc_test
    aoc_test.c
)

target_link_libraries(aoc_test PUBLIC check pthread aoc)

target_include_directories(aoc_test PUBLIC "${PROJECT_BINARY_DIR}")

add_test(NAME aoc_test COMMAND aoc_test WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(aoc_test PROPERTIES TIMEOUT 30)
