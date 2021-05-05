#include "kernel/kernel.hpp"

extern "C" void kernel_main()
{
    TTY::default_char_attr = TTY_NORMAL;
    TTY::print_str("Hello there", TTY_NORMAL);
}