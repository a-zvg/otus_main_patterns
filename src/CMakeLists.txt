cmake_minimum_required(VERSION 3.2)

option(CMAKE_ENABLE_DEBUG OFF)
option(CMAKE_ENABLE_TEST OFF)

project(${PROJECT} VERSION 0.1)

set(CMAKE_VERBOSE_MAKEFILE TRUE)

if(NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_PREFIX_PATH}/bin)
endif()

if(CMAKE_ENABLE_DEBUG)
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")
else()
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

#file(GLOB SRC "*.cpp")

#add_executable(${PROJECT_NAME} ${SRC})
#target_link_libraries(${PROJECT_NAME} pthread)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_PREFIX_PATH}/include
)
link_directories(
    ${CMAKE_PREFIX_PATH}/lib
)

# target test
if(CMAKE_ENABLE_TEST)
    enable_testing()
    add_subdirectory(test)
endif()
