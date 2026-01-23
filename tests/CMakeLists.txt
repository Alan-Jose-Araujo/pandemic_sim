# 1. Includes the Catch2 helper module to discover automatically tests
include(Catch)

set(TEST_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sample_data")

add_definitions(-DTEST_DATA_PATH="${TEST_DATA_DIR}")

# 2. Create the executable to the unit tests
add_executable(unit_tests
    unit/test_random_number_generator.cpp
    unit/test_json_parser.cpp
    unit/test_config.cpp
)

# 3. Link the dependencies
# - simulator_lib: provides the path to the headers (include/)
# - Catch2::Catch2WithMain: Provides the Catch2 library and generates the main() method automatically
target_link_libraries(unit_tests
    PRIVATE
    simulator_lib
    Catch2::Catch2WithMain
)

# 4. Set the CMake to discover every TEST_CASE individually.
# It allows to see the progress for each test with the 'ctest' command
catch_discover_tests(unit_tests)

# 5. Creates an executable to the functional tests
# add_executable(functional_tests 
#     functional/test_simulation_flow.cpp
# )

# target_link_libraries(functional_tests 
#     PRIVATE 
#         simulator_lib 
#         Catch2::Catch2WithMain
# )

# catch_discover_tests(functional_tests)