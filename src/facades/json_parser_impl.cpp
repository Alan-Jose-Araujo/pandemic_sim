/**
 * @file json_parser_impl.cpp
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-22
 */

#include "facades/json_parser.hpp"

namespace Facades
{
    bool JsonParser::isValidJson(const std::string &filePath)
    {
        try {
            std::ifstream file(filePath);
            if(!file.is_open()) {
                return false;
            }
            return JSON::accept(file);
        } catch(...) {
            return false;
        }
    }

    JSON JsonParser::getParser(const std::string &filePath)
    {
        std::ifstream inputFile(filePath);
        JSON jsonParser;
        inputFile >> jsonParser;
        return jsonParser;
    }
};