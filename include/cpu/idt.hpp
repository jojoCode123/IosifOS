#pragma once

#include "util/types.hpp"
#include "util/util.hpp"
#include "drivers/ports.hpp"
#include "cpu/general.hpp"

#define ISR_ENTRY_STUB __asm__("pusha")
#define ISR_EXIT_STUB __asm__("popa\n iret")
#define RESET_PIC port_out<uint8>(0x20, 0x20);port_out<uint8>(0xa0, 0x20)

namespace IDT
{
    // Structure of an IDT entry
    typedef struct
    {
        uint16 offset0_15;
        uint16 selector;
        uint8 zero;
        uint8 type;
        uint8 offset16_31;
    } S_idt_entry, *PS_idt_entry
    __attribute__((__packed__));

    typedef struct
    {
        uint16 size;
        uint32 location;
    } S_idt_desc, *PS_idt_desc
    __attribute__((__packed__));

    // Global IDT table
    extern "C" S_idt_entry GIDT[256];

    // Initialise the IDT
    void init_idt();

    // The default ISR
    void default_handler();

    // Construct an IDT entry
    S_idt_entry make_idt_entry(uint8 interrupt, void *handler, uint8 selector, uint8 type);

    // Initialise the PIC
    void init_pic(uint8 master_pic_offset, uint8 slave_pic_offset);

    // Load the idt
    void load_idt(PS_idt_desc idt_desc);
}