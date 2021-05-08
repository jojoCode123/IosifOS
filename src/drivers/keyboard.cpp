#include "drivers/keyboard.hpp"

namespace Keyboard
{
    namespace
    {
        bool left_shift_pressed;
        bool right_shift_pressed;
        bool left_control_pressed;
        bool right_control_pressed;
        bool left_alt_pressed;
        bool right_alt_pressed;
        bool caps_lock_enabled;
    }

    void keyboard_callback()
    {
        uint8 code = port_in<uint8>(KB_DATA_PORT);

        switch(code)
        {
            case 0x00:
            case 0xff:
                __asm__("int $0");
                return;

            case 0xee:
            case 0xfa:
            case 0xfc:
            case 0xfd:
                return;
        }

        switch(code)
        {
            case 0x1d:
                left_control_pressed = true;
                return;

            case 0x2a:
                left_shift_pressed = true;
                return;

            case 0x36:
                left_alt_pressed = true;

            case 0x3a:
                caps_lock_enabled ^= 1;
                toggle_caps_lock();
                return;

            case 0x9d:
                left_control_pressed = false;

            case 0xaa:
                left_shift_pressed = false;

            case 0xb6:
                right_shift_pressed = false;

            case 0xb8:
                left_alt_pressed = false;
        }

        char chr = codes[code];

        if(code < 58)
        {
            bool cap;

            if(caps_lock_enabled && (left_shift_pressed || right_shift_pressed))
            {
                cap = false;
            }
            else if(caps_lock_enabled)
            {
                cap = true;
            }
            else if(left_shift_pressed || right_shift_pressed)
            {
                cap = true;
            }
            else
            {
                cap = false;
            }

            if((chr >= 0x61 && chr <= 0x7a) && cap)
            {
                chr -= 0x20;
            }

            if(input_buffer_pointer >= 16384)
            {
                return;
            }

            if(chr == '\b')
            {
                if(input_buffer_pointer != 0)
                {
                    TTY::print_char(chr, NULL);
                    input_buffer_pointer--;
                }
                return;
            }

            if(chr == '\t')
            {
                for(uint8 i = 0; i < 4; i++)
                {
                    KB_INPUT_BUFFER[input_buffer_pointer++] = ' ';
                }
                TTY::print_char(chr, NULL);
                return;
            }

            KB_INPUT_BUFFER[input_buffer_pointer++] = chr;
            TTY::print_char(chr, NULL);
        }

        return;
    }

    size_t read(char buffer[], size_t length, char delimiter)
    {
        if(input_buffer_pointer >= length)
        {
            for(uint32 i = 0; i < length; i++)
            {
                char chr = KB_INPUT_BUFFER[i];
                if(chr == delimiter)
                {
                    length = ++i;
                    break;
                }
            }

            Memory::memc<char>(KB_INPUT_BUFFER, buffer, length);
            Memory::memc<char>(KB_INPUT_BUFFER + length, KB_INPUT_BUFFER, input_buffer_pointer - length);
            input_buffer_pointer -= length;
            return length;
        }

        while(true)
        {
            if(input_buffer_pointer == length)
            {
                break;
            }

            if(KB_INPUT_BUFFER[input_buffer_pointer - 1] == delimiter)
            {
                break;
            }
        }

        length = input_buffer_pointer;

        Memory::memc(KB_INPUT_BUFFER, buffer, length);
        Memory::memc(KB_INPUT_BUFFER + length, KB_INPUT_BUFFER, input_buffer_pointer - length);
        input_buffer_pointer -= length;
        buffer[length - 1] = 0;
        return length;
    }

    void toggle_caps_lock()
    {
        port_out<uint8>(KB_DATA_PORT, KB_SET_LED);
        port_out<uint8>(KB_DATA_PORT, KB_CAPS_LOCK);
        return;
    }
}