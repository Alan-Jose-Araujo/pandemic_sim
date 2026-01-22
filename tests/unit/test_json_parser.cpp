#include <catch2/catch_test_macros.hpp>
#include "facades/json_parser.hpp"
#include <string>

using FC = Facades::JsonParser;

// TEST_DATA_PATH was defined by CMake
std::string exampleFilesBaseDir = std::string(TEST_DATA_PATH) + "/";

TEST_CASE("JsonParser can access and use an example file", "[json][unit]")
{
    std::string exampleFile = exampleFilesBaseDir + "/json_parser_example_file.json";
    SECTION("Parser can find and validate the file")
    {
        REQUIRE_NOTHROW(FC::isValidJson(exampleFile));
    }
}

TEST_CASE("JsonParser can get the sample key value")
{
    std::string exampleFile = exampleFilesBaseDir + "/json_parser_example_file.json";
    std::string expectedValue = "Example text";
    JSON localParser = FC::getParser(exampleFile);
    REQUIRE(localParser.value("sample_key", "") == expectedValue);
}

TEST_CASE("JsonParser cannot validate the example file")
{
    std::string invalidFile = exampleFilesBaseDir + "/invalid_json_file.json";
    REQUIRE(!FC::isValidJson(invalidFile));
}