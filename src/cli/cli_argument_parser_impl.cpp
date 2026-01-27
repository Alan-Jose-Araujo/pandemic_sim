/**
 * @file cli_argument_parser_impl.cpp
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-26
 */

#include "cli/cli_argument_parser.hpp"
#include <vector>
#include <stdexcept>

namespace Cli
{
    void CliArgumentParser::addOption(char shortCode, const std::string &longName, CliArgumentType argumentType, Callback callback)
    {
        options[shortCode] = { longName, argumentType, callback };
    }

    void CliArgumentParser::parse(int argc, char *argv[])
    {
        std::vector<struct option> longOptions;
        std::string optString = "";

        for(auto const &[code, data] : options) {
            optString += code;
            if(data.argumentType != CliArgumentType::None) optString += ':';

            longOptions.push_back({
                data.longName.c_str(),
                data.argumentType,
                nullptr,
                code
            });
        }
        longOptions.push_back({0, 0, 0, 0});

        int opt;
        int optionIndex = 0;
        optind = 1;

        while((opt = getopt_long(argc, argv, optString.c_str(), longOptions.data(), &optionIndex)) != -1) {
            if(options.count(opt)) {
                options[opt].callback(optarg ? optarg : "");
            } else {
                throw std::runtime_error("Unknow option character: " + (char)opt);
            }
        }
    }
};