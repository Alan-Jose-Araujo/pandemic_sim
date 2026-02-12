/**
* @file cliparser.hpp
* @brief Register options and call the respective callbacks.
*/

#pragma once

#include <vector>
#include "pandemic_sim/cli/clioption.hpp"

/**
 * @class CliParser
 * Properties: std::vector<CliOption> options,
 * std::string applicationName.
 * Methods: explicit CliParser,
 * void addOption,
 * void parse,
 * void printHelp.
 */
namespace Cli
{
    class CliParser
    {
    private:

        std::vector<CliOption> options;

        std::string applicationName;

    public:

        explicit CliParser(const std::string& applicationName);

        void addOption(char shortName, const std::string& longName, ArgType argType, const std::string& desc, ArgumentCallback argumentCallback);

        void parse(int argc, char* argv[]);

        void printHelp() const;
    };
};