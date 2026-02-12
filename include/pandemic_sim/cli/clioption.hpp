/**
* @file clioption.hpp
* @brief Cli argument representation.
*/

#pragma once

#include <string>
#include <functional>
#include "pandemic_sim/cli/argtype.hpp"

/**
 * @struct CliOption
 * Members: char shortName,
 * std::string longName,
 * Cli::ArgType argType,
 * std::string description,
 * Cli::ArgumentCallback callback.
 */
namespace Cli
{
    // The callback receives the option value (empty string if not exists).
    using ArgumentCallback = std::function<void(const std::string&)>;

    struct CliOption
    {
        char shortName; // Short option code.
        std::string longName; // Full option name.
        ArgType argType; // Argument type (if has none, required or optional argument).
        std::string description; // Brief description of argument usage.
        ArgumentCallback callback; // Argument action.
    };
};