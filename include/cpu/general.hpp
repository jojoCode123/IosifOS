#pragma once

#define CLEAR_INTERRUPTS __asm__("cli")
#define ENABLE_INTERRUPTS __asm__("sti")