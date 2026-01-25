#include <catch2/catch_test_macros.hpp>
#include "facades/fs_handler.hpp"
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("FsHandler can create directory")
{
    SECTION("Can create directory if not exists", "[fshandler][unit]")
    {
        std::string directoryPath = "./dir_created_from_scratch";
        REQUIRE_NOTHROW(Facades::FsHandler::createDirectoryIfNotExists(directoryPath));
        REQUIRE(fs::exists(directoryPath));
    }
}