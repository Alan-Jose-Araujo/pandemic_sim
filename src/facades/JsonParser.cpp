#include "../../include/facades/JsonParser.hpp"
#include <fstream>
#include <stdexcept>

namespace facades
{

    JsonParser::JsonParser(const std::string json_file_path)
    : json_file_path(json_file_path)
    {
        std::ifstream file(json_file_path);

        // Check if the json file could be open.
        if(!file.is_open()) {
            throw std::runtime_error("[ERROR]: Failed to open JSON file: " + json_file_path);
        }

        // Check if the file contains a valid json syntax.
        if(!json::accept(file)) {
            throw std::runtime_error("[ERROR]: Invalid JSON syntax in file: " + json_file_path);
        }

        // Reopen the file because the json::accept consume the stream.
        file.clear();
        file.seekg(0, std::ios::beg);

        // Populates the base json parser.
        file >> base_parser;
    }

    bool JsonParser::is_valid_json(const std::string json_file_path)
    {
        std::ifstream file(json_file_path);
        if(!file.is_open()) return false;
        return json::accept(file);
    }

    const json& JsonParser::get_base_parser() const
    {
        return base_parser;
    }

};