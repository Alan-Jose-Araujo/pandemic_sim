#include "../../include/cli_argument_parser/CliArgumentParser.hpp"

namespace cli_argument_parser
{

    CliArgumentParser::CliArgumentParser(const char* short_options, const std::vector<option>& long_options)
    : short_options(short_options),
    long_options(long_options)
    {}

    void CliArgumentParser::parse(int argc, char* argv[], const std::function<void(int, const char*)>& callback)
    {
        int cli_option;
        std::vector<option> options = long_options;

        // 'getopt_long' function requires a C-style array, so add the terminator at the end.
        options.push_back({ nullptr, 0, nullptr, 0 });

        while((cli_option = getopt_long(argc, argv, short_options, options.data(), nullptr)) != -1) {
            callback(cli_option, optarg);
        }
    }

};