#include "drivers/video.hpp"

namespace VideoDriver
{
    void check_position(PS_cursor_position position)
    {
        position->row %= VIDEO_HEIGHT;
        position->column %= VIDEO_WIDTH;

        return;
    }

    uint16 position_to_offset(S_cursor_position position)
    {
        uint16 offset;

        check_position(&position);

        offset = position.row * VIDEO_WIDTH + position.column;

        return offset;
    }

    S_cursor_position offset_to_position(uint16 offset)
    {
        S_cursor_position position;

        position.column = offset % VIDEO_WIDTH;
        position.row = (offset - position.column) / VIDEO_WIDTH;

        return position;
    }

    S_cursor_position get_curor_position()
    {
        uint16 offset;
        S_cursor_position position;

        port_out<uint8>(VIDEO_CMD_PORT, VIDEO_SELECT_VERTICAL);
        offset = (uint16)port_in<uint8>(VIDEO_DATA_PORT) << 8;

        port_out<uint8>(VIDEO_CMD_PORT, VIDEO_SELECT_HORIZONTAL);
        offset += port_in<uint8>(VIDEO_DATA_PORT);

        position = offset_to_position(offset);

        return position;
    }

    void set_cursor_position(S_cursor_position position)
    {
        uint16 offset;

        check_position(&position);

        offset = position_to_offset(position);

        port_out<uint8>(VIDEO_CMD_PORT, VIDEO_SELECT_VERTICAL);
        port_out<uint8>(VIDEO_DATA_PORT, (uint8)(offset >> 8));
        port_out<uint8>(VIDEO_CMD_PORT, VIDEO_SELECT_HORIZONTAL);
        port_out<uint8>(VIDEO_DATA_PORT, (uint8)offset);

        return;
    }
}