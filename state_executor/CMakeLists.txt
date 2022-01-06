file(GLOB SRC src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC})
target_link_libraries(${PROJECT_NAME} ${TBB_LIBRARIES})

add_subdirectory(tests)
