add_executable(c_test ../src/c.c c_test.c)

target_link_libraries(c_test PUBLIC check pthread)

target_include_directories(c_test PUBLIC "${PROJECT_BINARY_DIR}")

add_test(NAME c_test COMMAND c_test WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Testing)
set_tests_properties(c_test PROPERTIES TIMEOUT 30)