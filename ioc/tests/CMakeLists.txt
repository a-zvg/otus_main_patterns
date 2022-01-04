add_executable(ioc_test ioc_test.cpp)
target_link_libraries(ioc_test ioc ${GTest_LIBRARIES})
add_test(NAME ioc_test COMMAND ioc_test)

add_executable(ioc_mt_test ioc_mt_test.cpp)
target_link_libraries(ioc_mt_test ioc ${GTest_LIBRARIES})
add_test(NAME ioc_mt_test COMMAND ioc_mt_test)
