cmake_minimum_required(VERSION 3.20)
project(PandemicSim VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(Threads REQUIRED)

option(ENABLE_SANITIZERS "Compile With AddressSanitizer/ThreadSanitizer" OFF)
if(ENABLE_SANITIZERS)
    add_compile_options(-fsanitize=thread -g -O1)
    add_link_options(-fsanitize=thread)
endif()

add_subdirectory(src)

option(BUILD_TESTS "Compile Tests" ON)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()