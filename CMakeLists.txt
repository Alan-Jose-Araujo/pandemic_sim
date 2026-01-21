cmake_minimum_required(VERSION 3.10)
project(PandemicSim VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Dependências Externas ---
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0 
)
FetchContent_MakeAvailable(Catch2)

# --- Configuração da Biblioteca e Executável ---

# Coleta todos os .cpp, mas separa o main.cpp
file(GLOB_RECURSE ALL_SOURCES "src/*.cpp")
set(LIB_SOURCES ${ALL_SOURCES})
list(FILTER LIB_SOURCES EXCLUDE REGEX "src/main.cpp")

# Cria a biblioteca lógica
add_library(simulator_lib ${LIB_SOURCES})

# O PUBLIC aqui é a "mágica": ele propaga o caminho /include 
# para o executável 'simulator' e para os 'tests' automaticamente.
target_include_directories(simulator_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Executável Principal (agora usando explicitamente o src/main.cpp)
add_executable(simulator src/main.cpp)
target_link_libraries(simulator PRIVATE simulator_lib)

# --- Testes ---
enable_testing()
add_subdirectory(tests)