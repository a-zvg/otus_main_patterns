cmake_minimum_required(VERSION 3.2)

project(ioc VERSION 0.1)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
    message(STATUS "CMAKE_BUILD_TYPE is not specified. Using default: ${CMAKE_BUILD_TYPE}")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (MSVC)
    add_compile_options("/W3")
else()
    add_compile_options("-Wall" "-Wextra")
    set(CMAKE_VERBOSE_MAKEFILE TRUE)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

include(${CMAKE_SOURCE_DIR}/conan.cmake)

conan_cmake_configure(REQUIRES gtest/1.11.0
                               boost/1.78.0
                      GENERATORS cmake_find_package
                      IMPORTS "bin, *.dll -> ./bin"
                      IMPORTS "lib, *.dylib* -> ./bin"
                      OPTIONS boost:header_only=True)

conan_cmake_install(PATH_OR_REFERENCE .
                    BUILD missing
                    REMOTE conancenter)

# разрешение зависимостей
find_package(GTest REQUIRED)
find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}
                    ${GTest_INCLUDE_DIR}
                    ${Boost_INCLUDE_DIR})

# включение тестов
enable_testing()

# сборка исходников
add_subdirectory(ioc)
