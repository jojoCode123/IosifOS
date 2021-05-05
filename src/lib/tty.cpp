#include "lib/tty.hpp"

namespace TTY
{
    uint8 default_char_attr;

    void print_char_at(char chr, uint8 attr, S_cursor_position position)
    {
        uint16 offset;
        ushort value;

        set_cursor_position(position);
        offset = position_to_offset(position);
        value = (ushort)SHL(attr, 8) + (ushort)chr;
        P_VIDEO_MEMORY[offset] = value;

        move_cursor(RIGHT);

        return;
    }

    void print_char(char chr, uint8 attr)
    {
        S_cursor_position current_position;

        current_position = get_curor_position();
        
        if(chr == '\n')
        {
            print_nl(attr);
        }
        else if(chr == '\r')
        {
            current_position.column = 0;
            set_cursor_position(current_position);
        }
        else if(chr == '\b')
        {
            print_backspace(attr);
        }
        else if(chr == '\t')
        {
            for(uint8 i = 0; i < 4; i++)
            {
                print_char(' ', attr);
            }
        }
        else
        {
            print_char_at(chr, attr, current_position);
        }

        return;
    }

    void print_str_at(STRING string, uint8 attr, S_cursor_position position)
    {
        set_cursor_position(position);
        for(uint32 i = 0; string[i] != 0; i++)
        {
            print_char(string[i], attr);
        }

        return;
    }

    void print_str(STRING string, uint8 attr)
    {
        S_cursor_position current_position;

        current_position = get_curor_position();
        print_str_at(string, attr, current_position);

        return;
    }

    void print_nl(uint8 attr)
    {
        S_cursor_position current_position;

        current_position = get_curor_position();
        move_cursor(DOWN);
        current_position.column = 0;

        return;
    }

    void print_backspace(uint8 attr)
    {
        move_cursor(LEFT);
        print_char_at(' ', attr, get_curor_position());
        move_cursor(LEFT);

        return;
    }

    void move_cursor(E_move_direction direction)
    {
        S_cursor_position current_position;

        current_position = get_curor_position();
        switch(direction)
        {
            case LEFT:
                if(current_position.column == 0)
                {
                    if(current_position.row == 0)
                    {
                        return;
                    }
                    else
                    {
                        current_position.row--;
                        current_position.column = VIDEO_WIDTH - 1;
                    }
                }
                else
                {
                    current_position.column--;
                }
                set_cursor_position(current_position);

                return;

            case RIGHT:
                if(current_position.column == VIDEO_WIDTH - 1)
                {
                    if(current_position.row == VIDEO_HEIGHT - 1)
                    {
                        scroll(default_char_attr);
                        current_position.row = VIDEO_HEIGHT - 1;
                        current_position.column = 0;
                    }
                    else
                    {
                        current_position.row++;
                        current_position.column = 0;
                    }
                }
                else
                {
                    current_position.column++;
                }
                set_cursor_position(current_position);

                return;

            case DOWN:
                if(current_position.row == VIDEO_HEIGHT - 1)
                {
                    scroll(default_char_attr);
                    return;
                }
                else
                {
                    current_position.row++;
                }
                set_cursor_position(current_position);

                return;

            case UP:
                if(current_position.row == 0)
                {
                    return;
                }
                else
                {
                    current_position.row--;
                }
                set_cursor_position(current_position);

                return;
        }
    }

    void clear_screen(uint8 attr, bool set_to_beginning)
    {
        char chr;
        ushort value;
        S_cursor_position position;

        if(!attr)
        {
            attr = default_char_attr;
        }

        chr = ' ';
        value = (ushort)SHL(chr, 8) + (ushort)attr;

        Memory::mems<ushort>((ushort *)P_VIDEO_MEMORY, value, VIDEO_HEIGHT * VIDEO_WIDTH);

        if(set_to_beginning)
        {
            position.column = 0;
            position.row = 0;
            set_cursor_position(position);
        }

        return;
    }

    void scroll(uint8 lines)
    {
        uint8 attr;
        char chr;
        ushort value;

        attr = default_char_attr;
        chr = ' ';
        value = (ushort)SHL(chr, 8) + (ushort)attr;

        Memory::memc<ushort>(&P_VIDEO_MEMORY[lines*VIDEO_WIDTH], P_VIDEO_MEMORY, VIDEO_SIZE - lines*VIDEO_WIDTH);
        Memory::mems<ushort>(&P_VIDEO_MEMORY[VIDEO_SIZE - lines*VIDEO_WIDTH], value, lines*VIDEO_WIDTH);

        return;
    }

    uint8 make_attr(uint8 foreground, uint8 background, bool blink)
    {
        uint8 value = 0;

        if(blink)
        {
            value |= ATTR_BLINK;
        }

        value |= foreground;
        value |= SHL(background, 4);

        return value;
    }
}