#pragma once

#include "util/types.hpp"
#include "util/util.hpp"
#include "lib/memory.hpp"


namespace GDT
{
    // The globally stored GDT

    // Structure of GDT descriptor
    typedef struct
    {
        uint16 size;
        uint32 location;
    } S_gdt_desc, *PS_gdt_desc;

    typedef struct
    {
        uint8 Ac:1;
        uint8 RW:1;
        uint8 DC:1;
        uint8 Ex:1;
        uint8 S:1;
        uint8 Privl:2;
        uint8 Pr:1;
    } S_gdt_access, *PS_gdt_access
    __attribute__((__packed__));

    // Structure of GDT entry
    typedef struct
    {
        uint8 limit0_7;
        uint8 limit8_15;
        uint8 base0_7;
        uint8 base8_15;
        uint8 base16_23;
        //S_gdt_access access;
        uint8 access;
        uint8 limit16_19:4;
        uint8 flags:4;
        uint8 base24_31;
    } S_gdt_entry, *PS_gdt_entry
    __attribute__((__packed__));

    
    // Initialise the GDT
    void init_gdt();
    // Load the GDT descriptor into the gdt register

    void load_gdt();

    extern "C" S_gdt_entry GGDT[3];
}