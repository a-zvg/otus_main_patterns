file(GLOB SRC common/*.cpp
              fuel/*.cpp
              move/*.cpp
              rotate/*.cpp)
add_library(macro_command STATIC ${SRC})

add_subdirectory(tests)
