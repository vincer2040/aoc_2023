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
    day1_test
    day1_test.c
)

target_link_libraries(day1_test PUBLIC check pthread day1)

target_include_directories(day1_test PUBLIC "${PROJECT_BINARY_DIR}")

add_test(NAME day1_test COMMAND day1_test WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(day1_test PROPERTIES TIMEOUT 30)
