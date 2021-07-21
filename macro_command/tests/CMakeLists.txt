add_executable(macro_command_test macro_command_test.cpp)
target_link_libraries(macro_command_test macro_command ${GTest_LIBRARIES} Threads::Threads)
add_test(NAME macro_command_test COMMAND macro_command_test)

add_executable(check_fuel_test check_fuel_test.cpp)
target_link_libraries(check_fuel_test macro_command ${GTest_LIBRARIES} Threads::Threads)
add_test(NAME check_fuel_test COMMAND check_fuel_test)

add_executable(burn_fuel_test burn_fuel_test.cpp)
target_link_libraries(burn_fuel_test macro_command ${GTest_LIBRARIES} Threads::Threads)
add_test(NAME burn_fuel_test COMMAND burn_fuel_test)

add_executable(move_command_with_burn_fuel_test move_command_with_burn_fuel_test.cpp)
target_link_libraries(move_command_with_burn_fuel_test macro_command ${GTest_LIBRARIES} Threads::Threads)
add_test(NAME move_command_with_burn_fuel_test COMMAND move_command_with_burn_fuel_test)
