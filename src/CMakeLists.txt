add_library(
    pandemic_core # Library name
    HelloWorld.cpp
)

target_include_directories(
    pandemic_core
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
    pandemic_core
    PUBLIC Threads::Threads
)

add_executable(
    pandemic_sim
    main.cpp
)

target_link_libraries(
    pandemic_sim
    PRIVATE
    pandemic_core
)