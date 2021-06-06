cmake_minimum_required(VERSION 3.2)

option(ENABLE_TEST "Enable testing" ON)

project(movement VERSION 0.1)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
    message(STATUS "CMAKE_BUILD_TYPE is not specified. Using default: ${CMAKE_BUILD_TYPE}")
endif()

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")

find_package(Threads REQUIRED)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

#file(GLOB_RECURSE SRC "src/*.cpp")
#add_library(${PROJECT_NAME} ${SRC})
#target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS} Threads::Threads)
include_directories(${CMAKE_SOURCE_DIR}/src)

# target test
if (ENABLE_TEST)
    enable_testing()
    add_subdirectory(test)
endif()
