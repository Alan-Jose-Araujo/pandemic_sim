#ifndef CLI_ARGUMENT_PARSER_HPP
#define CLI_ARGUMENT_PARSER_HPP

#include <vector>
#include <getopt.h>
#include <functional>

namespace cli_argument_parser
{

    class CliArgumentParser
    {

        private:

            const char* short_options;

            std::vector<option> long_options;

        public:

            CliArgumentParser(const char* short_options, const std::vector<option>& long_options);

            void parse(int argc, char* argv[], const std::function<void(int, const char*)>& callback);

    };

};

#endif