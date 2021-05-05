#pragma once

#include "lib/tty.hpp"
#include "cpu/gdt.hpp"
#include "cpu/idt.hpp"

// Kernel entry
extern "C" void kernel_main();