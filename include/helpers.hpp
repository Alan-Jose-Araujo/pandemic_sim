#pragma once

#include <string>

inline std::string bool_to_string(bool boolean_value)
{
    return boolean_value ? "Yes" : "No";
}