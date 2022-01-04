file(GLOB SRC src/*.cpp)
add_library(ioc STATIC ${SRC})

add_subdirectory(tests)
