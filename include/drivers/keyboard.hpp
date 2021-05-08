#include "drivers/ports.hpp"
#include "lib/tty.hpp"

#define KB_DATA_PORT 0x60
#define KB_COMMAND_PORT 0x64

#define KB_SET_LED 0xed
#define KB_ECHO 0xee
#define KB_GET_SCANCODE_SET 0xf0
#define KB_SET_SCANCODE_SET 0xf0
#define KB_ID 0xf2
#define KB_SET_RATE 0xf3
#define KB_ENABLE_SCANNING 0xf4
#define KB_DISABLE_SCANNING 0xf5
#define KB_SET_DEFAULT 0xf6
#define KB_SET_TYPEMATIC_AUTOREPEAT 0xf7
#define KB_SET_MAKE_RELEASE 0xf8
#define KB_SET_MAKE 0xf9
#define KB_SET_TYPEMATIC_AUTOREPEAT_MAKE_RELEASE 0xfa
#define KB_SET_KEY_TYPEMATIC_AUTOREPEAT 0xfb
#define KB_SET_KEY_MAKE_RELEASE 0xfc
#define KB_SET_KEY_MAKE 0xfd
#define KB_RESEND 0xfe
#define KB_RESET_TEST 0xff

#define KB_ERROR_0 0x00
#define KB_TEST_PASSED 0xaa
#define KB_ECHO_RESPONSE 0xee
#define KB_ACK 0xfa
#define KB_TEST_FAILED 0xfc
#define KB_RESEND_CMD 0xfe
#define KB_ERROR_F 0xff

#define KB_SCROLL_LOCK 0x00
#define KB_NUM_LOCK 0x01
#define KB_CAPS_LOCK 0x02

#define KB_GET_SCANCODE_SET_S 0x00
#define KB_SET_SCANCODE_SET_1 0x01
#define KB_SET_SCANCODE_SET_2 0x02
#define KB_SET_SCANCODE_SET_3 0x03

namespace Keyboard
{
    const char codes[]
    {
    0x00, 0x01, '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', '0', '-',
    '=', '\b', '\t', 'q',
    'w', 'e', 'r', 't',
    'y', 'u', 'i', 'o',
    'p', '[', ']', '\n',
    0x1d,
    'a', 's', 'd', 'f',
    'g', 'h', 'j', 'k',
    'l', ';', '\'', '`',
    0x2a, '\\', 'z', 'x',
    'c', 'v', 'b', 'n',
    'm', ',', '.', '/',
    0x36, '*', 0x38, ' ',
    0x3a
    };

    extern "C" char KB_INPUT_BUFFER[];
    static uint32 input_buffer_pointer;

    // Default callback function for keyboard interrupt
    void keyboard_callback();

    // Reads max X bytes, or until delimiter is reached,
    // from input buffer.
    // Removes the read data from the buffer and copies any
    // remaining data to the beginning
    // Returns bytes read
    size_t read(char buffer[], size_t size, char delimiter);

    void toggle_caps_lock();
}