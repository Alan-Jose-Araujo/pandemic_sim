cmake_minimum_required(VERSION 3.10)
project(PandemicSim VERSION 1.0)

# Defining C++ standard.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Defining sources directory.
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(simulator ${SOURCES})

# Defining the root include directory.
target_include_directories(simulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)