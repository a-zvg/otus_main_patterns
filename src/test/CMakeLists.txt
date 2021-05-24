set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_PREFIX_PATH}/bin/test)

add_executable(movement_test movement_test.cpp)
target_link_libraries(movement_test gtest gmock gmock_main pthread)
add_test(NAME movement_test COMMAND movement_test)

add_executable(rotating_test rotating_test.cpp)
target_link_libraries(rotating_test gtest gmock gmock_main pthread)
add_test(NAME rotating_test COMMAND rotating_test)
