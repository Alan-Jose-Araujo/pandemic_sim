#include <getopt.h>
#include <iostream>
#include "pandemic_sim/cli/cliparser.hpp"

namespace Cli
{
    CliParser::CliParser(const std::string& applicationName)
        : applicationName(applicationName) {}

    void CliParser::addOption(char shortName, const std::string& longName, ArgType argType, const std::string& desc, ArgumentCallback argumentCallback)
    {
        this->options.push_back({shortName, longName, argType, desc, argumentCallback});
    }

    void CliParser::parse(int argc, char* argv[])
    {
        // Local options registry.
        std::string shortOptions;
        std::vector<struct option> longOptionsC;

        // Build the getopt_long structures.
        for (const auto& option : this->options)
        {
            shortOptions += option.shortName;

            // Define the mandatory argument.
            int hasArgumentValue = no_argument;
            if (option.argType == ArgType::Required)
            {
                shortOptions += ":";
                hasArgumentValue = required_argument;
            } else if (option.argType == ArgType::Optional)
            {
                shortOptions += "::";
                hasArgumentValue = optional_argument;
            }

            struct option longOption;
            longOption.name = option.longName.c_str();
            longOption.has_arg = hasArgumentValue;
            longOption.flag = nullptr;
            longOption.val = option.shortName;

            longOptionsC.push_back(longOption);
        }

        // C-style array terminator (required by getopt_long).
        longOptionsC.push_back({nullptr, 0, nullptr, 0});

        int opt;
        int optionIndex = 0;
        optind = 1;

        while ((opt = getopt_long(argc, argv, shortOptions.c_str(), longOptionsC.data(), &optionIndex)) != -1)
        {
            if (opt == '?')
            {
                // Capture invalid options and exit from program.
                exit(EXIT_FAILURE);
            }

            // Finds the respective option.
            for (const auto& registeredOption : this->options)
            {
                if (registeredOption.shortName == opt)
                {
                    std::optional<std::string> argValue = std::nullopt;
                    if (optarg)
                    {
                        argValue = std::string(optarg);
                    }
                    // NULL as default.
                    registeredOption.argumentCallback(argValue);
                    break;
                }
            }
        }
    }

    void CliParser::printHelp() const
    {
        std::cout << "Usage: " << this->applicationName << " [options]\nOptions:\n" << std::endl;
        for (const auto& option : this->options)
        {
            std::cout << " -" << option.shortName << ", --" << option.longName;
            if (option.argType == ArgType::Required) std::cout << " <arg>";
            else if (option.argType == ArgType::Optional) std::cout << " [arg]";

            std::cout << "\t" << option.description << "\n";
        }
        std::cout << std::endl;
    }
};