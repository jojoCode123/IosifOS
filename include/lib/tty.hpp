#pragma once

#include "drivers/video.hpp"
#include "lib/memory.hpp"
#include "util/util.hpp"

#define TTY_WARNING TTY::make_attr(ATTR_WHITE, ATTR_RED, true)
#define TTY_NORMAL TTY::make_attr(ATTR_WHITE, ATTR_BLACK, false)
#define TTY_ERROR TTY::make_attr(ATTR_LIGHT_RED, ATTR_BLACK, false)
#define TTY_SUCCESS TTY::make_attr(ATTR_LIGHT_GREEN, ATTR_BLACK, false)

using namespace VideoDriver;

namespace TTY
{
    // For the move_cursor function
    enum E_move_direction
    {
        LEFT,
        RIGHT,
        DOWN,
        UP
    };

    // The default character attribute
    extern uint8 default_char_attr;

    // Print a character at a specific position
    void print_char_at(char chr, S_cursor_position position, uint8 attr = NULL);

    // Print a character at the current position
    void print_char(char chr, uint8 attr);

    // Prints a string at a specific position
    void print_str_at(const char *string, S_cursor_position position, uint8 attr = NULL);

    // Prints a string at the current position
    void print_str(const char *string, uint8 attr = NULL);

    // Print a new line
    void print_nl(uint8 attr = NULL);

    // Print a backspace
    void print_backspace(uint8 attr = NULL);

    // Move the cursor
    void move_cursor(E_move_direction direction);

    // Clear the sreen
    void clear_screen(bool set_to_beginning, uint8 attr = NULL);

    // Scroll the screen X lines
    void scroll(uint8 lines);

    // Construct an attribute
    uint8 make_attr(uint8 foreground, uint8 background, bool blink);
}