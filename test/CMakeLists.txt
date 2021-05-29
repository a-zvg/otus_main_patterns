add_executable(movement_test movement_test.cpp)
target_link_libraries(movement_test ${CONAN_LIBS} Threads::Threads)
add_test(NAME movement_test COMMAND movement_test)

add_executable(rotating_test rotating_test.cpp)
target_link_libraries(rotating_test ${CONAN_LIBS} Threads::Threads)
add_test(NAME rotating_test COMMAND rotating_test)
