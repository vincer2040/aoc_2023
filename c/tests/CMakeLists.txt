include(FetchContent)

set(LIBCHECK_VERSION "0.15.2")

# Use FetchContent to download and include libcheck
FetchContent_Declare(
    libcheck
    URL https://github.com/libcheck/check/archive/${LIBCHECK_VERSION}.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP true  # Specify the option here
)

FetchContent_MakeAvailable(libcheck)
add_executable(c_test ../src/c.c c_test.c)

target_link_libraries(c_test PUBLIC check pthread)

target_include_directories(c_test PUBLIC "${PROJECT_BINARY_DIR}")

add_test(NAME c_test COMMAND c_test WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(c_test PROPERTIES TIMEOUT 30)
