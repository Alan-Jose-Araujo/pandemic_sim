#include <catch2/catch_test_macros.hpp>
#include "facades/config.hpp"
#include "facades/json_parser.hpp"
#include <string>
#include <fstream>

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

TEST_CASE("Config file can be generated", "[config][unit]")
{
    SECTION("File can be generated without extension on output path")
    {
        std::string testFile = "./test_output";
        Facades::Config::generateConfigFile(testFile);
        std::ifstream check(testFile + ".json");
        REQUIRE(check.good());

        JSON json = JSON::parse(check);
        CHECK(json["number_of_runs"] == 0);
    }

    SECTION("File can be generated with extension on output path")
    {
        std::string testFile = "./test_output.json";
        Facades::Config::generateConfigFile(testFile);
        std::ifstream check(testFile);
        REQUIRE(check.good());

        JSON json = JSON::parse(check);
        CHECK(json["number_of_runs"] == 0);
    }
}