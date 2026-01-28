cmake_minimum_required(VERSION 3.10)
project(PandemicSim VERSION 1.0)

# --- Global Build Configurations ---

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- External Dependencies ---

include(FetchContent)

# Catch2
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)

# JSON
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)

# STB (Single-file public domain libraries)
FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb.git
  GIT_TAG master
)

FetchContent_MakeAvailable(Catch2 json stb)

# --- Source Files Management ---

file(GLOB_RECURSE ALL_SOURCES "src/*.cpp")
set(LIB_SOURCES ${ALL_SOURCES})
list(FILTER LIB_SOURCES EXCLUDE REGEX "src/main.cpp")

# --- Target Definitions ---

# 1. Create a logical target for STB since it's header-only
add_library(stb_headers INTERFACE)
target_include_directories(stb_headers INTERFACE ${stb_SOURCE_DIR})

# 2. Core Logic Library
add_library(simulator_lib ${LIB_SOURCES})
target_include_directories(simulator_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link JSON and STB to the library
# STB is linked as INTERFACE because we only need the header path
target_link_libraries(simulator_lib 
    PUBLIC 
        nlohmann_json::nlohmann_json
        stb_headers
)

# 3. Main Executable
add_executable(simulator src/main.cpp)
target_link_libraries(simulator PRIVATE simulator_lib)

# --- Platform-Specific Static Linking ---

if(WIN32 AND NOT MSVC)
    target_link_options(simulator PRIVATE -static -static-libgcc -static-libstdc++)
elseif(UNIX AND NOT APPLE)
    target_link_options(simulator PRIVATE -static)
endif()

# --- Distribution & Packaging (CPack) ---

install(TARGETS simulator DESTINATION bin)

set(CPACK_PACKAGE_NAME "PandemicSim")
set(CPACK_PACKAGE_VENDOR "AlanJose")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "ZIP;TGZ")

include(CPack)

# --- Test Suite ---

enable_testing()
add_subdirectory(tests)