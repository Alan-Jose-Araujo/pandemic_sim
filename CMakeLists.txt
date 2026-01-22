cmake_minimum_required(VERSION 3.10)
project(PandemicSim VERSION 1.0)

# --- Global Build Configurations ---

# Enable static runtime for MSVC (Windows)
if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

# Set C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- External Dependencies (Catch2 & JSON) ---

include(FetchContent)

# Fetching Catch2 for Unit Testing
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)

# Fetching nlohmann/json for Configuration Files
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.3
)

FetchContent_MakeAvailable(Catch2 json)

# --- Source Files Management ---

# Recursively collect all .cpp files from src/
file(GLOB_RECURSE ALL_SOURCES "src/*.cpp")
set(LIB_SOURCES ${ALL_SOURCES})

# Exclude main.cpp from the library source list to avoid multiple 'main' definitions
list(FILTER LIB_SOURCES EXCLUDE REGEX "src/main.cpp")

# --- Target Definitions ---

# Create the core logic library
add_library(simulator_lib ${LIB_SOURCES})

# Add include directories and propagate to dependent targets
target_include_directories(simulator_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link JSON library as a public dependency
target_link_libraries(simulator_lib PUBLIC nlohmann_json::nlohmann_json)

# Define the main executable
add_executable(simulator src/main.cpp)

# Link the executable with the core library
target_link_libraries(simulator PRIVATE simulator_lib)

# --- Platform-Specific Static Linking ---

if(WIN32 AND NOT MSVC)
    # Static linking for MinGW/Clang on Windows
    target_link_options(simulator PRIVATE -static -static-libgcc -static-libstdc++)
elseif(UNIX AND NOT APPLE)
    # Static linking for Linux (Ubuntu)
    target_link_options(simulator PRIVATE -static)
endif()

# --- Distribution & Packaging (CPack) ---

# Specify installation rules for the binary
install(TARGETS simulator DESTINATION bin)

# CPack Metadata
set(CPACK_PACKAGE_NAME "PandemicSim")
set(CPACK_PACKAGE_VENDOR "AlanJose")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_GENERATOR "ZIP;TGZ")

include(CPack)

# --- Test Suite ---

enable_testing()
add_subdirectory(tests)