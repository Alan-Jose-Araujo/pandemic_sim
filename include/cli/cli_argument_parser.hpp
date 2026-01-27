/**
 * @file cli_argument_parser.hpp
 * @brief A simple cli argument parser.
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-26
 */

#pragma once

#include <string>
#include <functional>
#include <map>
#include <getopt.h>

namespace Cli
{
    using Callback = std::function<void(const std::string &)>;

    enum CliArgumentType
    {
        Required = required_argument,
        Optional = optional_argument,
        None = no_argument
    };

    struct CliArgumentData
    {
        std::string longName;
        CliArgumentType argumentType;
        Callback callback;
    };

    class CliArgumentParser
    {
    private:
        std::map<char, CliArgumentData> options;

    public:
        void addOption(char shortCode, const std::string &longName, CliArgumentType argumentType, Callback callback);

        void parse(int argc, char *argv[]);
    };
};