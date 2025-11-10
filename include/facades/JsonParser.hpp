/**
 * JsonParser.hpp
 * @author Alan José <alanjsdelima@gmail.com>
 *
 * The JSON parser handle the json files.
 */

#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "../../vendor/json.hpp"
#include <string>

using json = nlohmann::json;

namespace facades
{

    class JsonParser
    {

        private:

            std::string json_file_path;

            json base_parser;

        public:

            JsonParser(const std::string &json_file_path);

            static bool is_valid_json(const std::string json_file_path);

            const json& get_base_parser() const;

    };

};

#endif