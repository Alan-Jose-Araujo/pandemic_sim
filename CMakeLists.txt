cmake_minimum_required(VERSION 3.10)
project(PandemicSim VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- External dependencies ---
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0 
)
FetchContent_MakeAvailable(Catch2)

# --- Configs for library and executable ---

# Get all the .cpp files, but the main.cpp
file(GLOB_RECURSE ALL_SOURCES "src/*.cpp")
set(LIB_SOURCES ${ALL_SOURCES})
list(FILTER LIB_SOURCES EXCLUDE REGEX "src/main.cpp")

# Create the logical library
add_library(simulator_lib ${LIB_SOURCES})

# Propagates the /include path to the executable 'simulator' and 'tests' automatically
target_include_directories(simulator_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Main executable (using explicitly the src/main.cpp)
add_executable(simulator src/main.cpp)
target_link_libraries(simulator PRIVATE simulator_lib)

# --- Tests ---
enable_testing()
add_subdirectory(tests)