#pragma once

#include "util/types.hpp"
#include "drivers/ports.hpp"

namespace VideoDriver
{
    #define VIDEO_MEMORY 0xb8000
    #define P_VIDEO_MEMORY ((ushort *)VIDEO_MEMORY)

    #define VIDEO_CMD_PORT 0x3d4
    #define VIDEO_DATA_PORT 0x3d5

    #define VIDEO_WIDTH 80
    #define VIDEO_HEIGHT 25
    #define VIDEO_SIZE VIDEO_WIDTH*VIDEO_HEIGHT

    #define ATTR_BLINK 0x80
    #define ATTR_BLACK 0x00
    #define ATTR_BLUE 0x01
    #define ATTR_GREEN 0x02
    #define ATTR_CYAN 0x03
    #define ATTR_RED 0x04
    #define ATTR_PURPLE 0x05
    #define ATTR_BROWN 0x06
    #define ATTR_GREY 0x07
    #define ATTR_DARK_GREY 0x08
    #define ATTR_LIGHT_BLUE 0x09
    #define ATTR_LIGHT_GREEN 0x0a
    #define ATTR_LIGHT_CYAN 0x0b
    #define ATTR_LIGHT_RED 0x0c
    #define ATTR_LIGHT_PURPLE 0x0d
    #define ATTR_YELLOW 0x0e
    #define ATTR_WHITE 0x0f

    #define VIDEO_SELECT_VERTICAL 0x0e
    #define VIDEO_SELECT_HORIZONTAL 0x0f

    typedef struct
    {
        uint8 row;
        uint8 column;
    } S_cursor_position, *PS_cursor_position;

    // Correct any values in a position structure
    void check_position(PS_cursor_position position);

    // Convert from a position struct to a linear offset
    uint16 position_to_offset(S_cursor_position position);

    // Convert from a linear offset to a position struct
    S_cursor_position offset_to_position(uint16 offset);

    // Returns a struct with the current position of the cursor
    S_cursor_position get_curor_position();

    // Sets the current cursor position
    void set_cursor_position(S_cursor_position position);
}