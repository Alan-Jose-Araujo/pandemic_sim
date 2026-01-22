/**
 * @file json_parser.hpp
 * @brief A parser to JSON files.
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-22
 */

#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <fstream>

using JSON = nlohmann::json;

namespace Facades
{
    class JsonParser
    {
    public:
        static bool isValidJson(const std::string &filePath);

        static JSON getParser(const std::string &filePath);
    };
};