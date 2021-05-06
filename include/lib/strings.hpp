#pragma once

#include "util/util.hpp"
#include "util/types.hpp"
#include "lib/math.hpp"
#include "lib/memory.hpp"

namespace Strings
{
    // Copies a string from source to destination
    STRING strc(STRING source, char *destination);

    // Safe version of strc
    STRING strc_s(STRING source, char *destination, size_t size);

    // Returns legnth of a string (terminator not included)
    size_t strl(STRING string);

    // Checks if both strings are EXACTLY the same
    // Returns true if they are the same
    bool strcmp_complete(STRING string1, STRING string2);

    // Checks if the first X bytes of the 2 strings are the same
    // Returns true if they are the same
    bool strcmp_partial(STRING string1, STRING string2, size_t length);

    // Removes all whitespace from a string
    // Returns the number of whitespace charaters removed
    uint32 remove_whitespace(STRING string);

    // Convert from byte to ASCII digit
    // Only converts the lower 4 bits
    char byte_to_ascii(uint8 byte);

    // Convert from an ASCII digit to a byte
    uint8 ascii_to_byte(char digit);

    // Convert a byte to a hexadecimal representation
    STRING byte_to_hex(uint8 byte);

    // Convert an array of bytes to a hexadecimal representation
    // Caller is responsible for passing an appropriate sized output string
    STRING bytes_to_hex(uint8 *bytes, char output[], size_t length);

    // Convert a single byte hex string to a byte
    uint8 hex_to_byte(STRING hex);

    // Convert an integer to an ASCII decimal representation
    STRING int_to_dec(uint32 value);

    // Convert an integer to an ASCII hexadecimal representation
    STRING int_to_hex(uint32 value);

    // Convert an ASCII decimal representation to an integer
    uint32 dec_to_int(STRING decimal);

    // Convert an ASCII hexadecimal representation to an integer
    uint32 hex_to_int(STRING hex);
}