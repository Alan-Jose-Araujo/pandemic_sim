#include <catch2/catch_test_macros.hpp>
#include "facades/config.hpp"
#include <string>

using CF = Facades::Config;

TEST_CASE("Config can be created from config file", "[config][unit]")
{
    std::string configFile = std::string(TEST_DATA_PATH) + "/json_config_file_example.json";

    SECTION("File exists and is valid")
    {
        REQUIRE_NOTHROW(Facades::Config::buildFromConfigFile(configFile));
    }

    SECTION("File does not exist")
    {
        std::string missingPath = std::string(TEST_DATA_PATH) + "/json_missing_config_file.json";

        REQUIRE_THROWS_AS(Facades::Config::buildFromConfigFile(missingPath), std::runtime_error);
    }

    SECTION("Malformed syntax file")
    {
        std::string malformedPath = std::string(TEST_DATA_PATH) + "/json_invalid_file_example.json";

        REQUIRE_THROWS_AS(Facades::Config::buildFromConfigFile(malformedPath), std::runtime_error);
    }

    SECTION("Config DTO is populated correctly")
    {
        Facades::Config configDto = Facades::Config::buildFromConfigFile(configFile);
        int expectedValue = 10;
        REQUIRE(configDto.getNumberOfRuns() == expectedValue);
    }
}