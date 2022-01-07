file(GLOB SRC src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC})

add_subdirectory(tests)
