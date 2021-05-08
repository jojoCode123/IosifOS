#pragma once

#include "util/util.hpp"
#include "util/types.hpp"
#include "lib/math.hpp"
#include "lib/memory.hpp"

namespace Strings
{
    // Copies a string from source to destination
    const char *strc(const char *source, char *destination);

    // Safe version of strc
    const char *strc_s(const char *source, char *destination, size_t size);

    // Returns legnth of a string (terminator not included)
    size_t strl(const char *string);

    // Checks if both strings are EXACTLY the same
    // Returns true if they are the same
    bool strcmp_complete(const char *string1, const char *string2);

    // Checks if the first X bytes of the 2 strings are the same
    // Returns true if they are the same
    bool strcmp_partial(const char *string1, const char *string2, size_t length);

    // Removes all whitespace from a string
    // Returns the number of whitespace charaters removed
    uint32 remove_whitespace(char *string);

    // Convert from byte to ASCII digit
    // Only converts the lower 4 bits
    char byte_to_ascii(uint8 byte);

    // Convert from an ASCII digit to a byte
    uint8 ascii_to_byte(char digit);

    // Convert a byte to a hexadecimal representation
    const char *byte_to_hex(uint8 byte);

    // Convert an array of bytes to a hexadecimal representation
    // Caller is responsible for passing an appropriate sized output string
    const char *bytes_to_hex(uint8 *bytes, char output[], size_t length);

    // Convert a single byte hex string to a byte
    uint8 hex_to_byte(const char *hex);

    // Convert an integer to an ASCII decimal representation
    const char *int_to_dec(uint32 value);

    // Convert an integer to an ASCII hexadecimal representation
    const char *int_to_hex(uint32 value);

    // Convert an ASCII decimal representation to an integer
    uint32 dec_to_int(const char *decimal);

    // Convert an ASCII hexadecimal representation to an integer
    uint32 hex_to_int(const char *hex);
}