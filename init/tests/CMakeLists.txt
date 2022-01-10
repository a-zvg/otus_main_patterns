add_executable(init_test init_test.cpp)
target_link_libraries(init_test init ${GTest_LIBRARIES})
add_test(NAME init_test COMMAND init_test)
