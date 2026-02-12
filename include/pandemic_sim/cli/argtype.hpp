/**
 * @file argtype.hpp
 * @brief Argument type enum for cli argument parser.
**/

#pragma once

/**
 * @class ArgType
 * Cases: None, Required, Optional.
 */
enum class ArgType
{
    None, // no_argument
    Required, // required_argument
    Optional // optional_argument
};