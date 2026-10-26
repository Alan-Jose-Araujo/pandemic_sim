include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(
    pandemic_tests
    test_hello_world.cpp
)

target_link_libraries(pandemic_tests
    PRIVATE
        pandemic_core
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(pandemic_tests)