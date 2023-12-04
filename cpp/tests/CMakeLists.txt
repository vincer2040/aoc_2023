include(FetchContent)
FetchContent_Declare(
    googletest
    URL     https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true  # Specify the option here
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_executable(
   day1_test
   day1_test.cc
)

target_link_libraries(
    day1_test
    GTest::gtest_main
    day1
)

add_executable(
   day2_test
   day2_test.cc
)

target_link_libraries(
    day2_test
    GTest::gtest_main
    day2
)

add_executable(
    day3_test
    day3_test.cc
)

target_link_libraries(
    day3_test
    GTest::gtest_main
    day3
)

include(GoogleTest)
gtest_discover_tests(day1_test)
gtest_discover_tests(day2_test)
gtest_discover_tests(day3_test)
