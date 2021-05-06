#pragma once

#include "lib/tty.hpp"
#include "cpu/gdt.hpp"
#include "cpu/idt.hpp"
#include "lib/strings.hpp"
#include "lib/dynamic.hpp"

// Kernel entry
extern "C" void kernel_main();