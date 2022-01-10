file(GLOB SRC common/src/*.cpp
              ioc/src/*.cpp
              move/src/*.cpp
              rotate/src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${SRC})

add_subdirectory(tests)
