cmake_minimum_required(VERSION 3.2)

option(ENABLE_TEST "Enable testing" ON)

project(multithreding VERSION 0.1)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
    message(STATUS "CMAKE_BUILD_TYPE is not specified. Using default: ${CMAKE_BUILD_TYPE}")
endif()

set(CMAKE_VERBOSE_MAKEFILE TRUE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra")

find_package(Threads REQUIRED)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB SRC "src/*.cpp")
add_library(${PROJECT_NAME} STATIC ${SRC})
include_directories(${CMAKE_SOURCE_DIR}/src)

# target test
if (ENABLE_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

# target doc
find_package(Doxygen QUIET)
if(DOXYGEN_FOUND)
    configure_file(Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile)
    add_custom_target(doc COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_BINARY_DIR}/Doxyfile)
else()
    message(STATUS "WARNING: doxygen not found - target \"doc\" will not be available")
endif()
