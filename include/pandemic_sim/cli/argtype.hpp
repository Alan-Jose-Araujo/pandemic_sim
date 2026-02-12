/**
* @file argtype.hpp
* @brief Argument type enum for cli argument parser.
*/

#pragma once

/**
 * @enum ArgType
 * Cases: None, Required, Optional.
 */
namespace Cli
{
    enum class ArgType
    {
        None, // no_argument
        Required, // required_argument
        Optional // optional_argument
    };
};