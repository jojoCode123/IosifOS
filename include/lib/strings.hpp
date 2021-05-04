#pragma once

#include "util/util.hpp"
#include "util/types.hpp"

namespace Strings
{
    // Copies a string from source to destination
    STRING strc(STRING source, char *destination);

    // Safe version of strc
    STRING strc_s(STRING source, char *destination, size_t size);

    // Returns legnth of a string (terminator not included)
    size_t strl(STRING string);

    // Checks if both strings are EXACTLY the same
}