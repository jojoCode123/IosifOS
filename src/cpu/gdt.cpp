#include "cpu/gdt.hpp"

namespace GDT
{
    void init_gdt()
    {
        S_gdt_desc gdt_desc;

        S_gdt_entry null_segment;
        S_gdt_entry code_segment;
        S_gdt_entry data_segment;

        S_gdt_access null_access;
        S_gdt_access code_access;
        S_gdt_access data_access;

        null_access.Ac = 0;
        null_access.DC = 0;
        null_access.Ex = 0;
        null_access.Pr = 0;
        null_access.Privl = 0;
        null_access.RW = 0;
        null_access.S = 0;

        null_segment.access = null_access;
        null_segment.base0_7 = 0;
        null_segment.base16_23 = 0;
        null_segment.base24_31 = 0;
        null_segment.base8_15 = 0;
        null_segment.flags = 0;
        null_segment.limit0_7 = 0;
        null_segment.limit16_19 = 0;
        null_segment.limit8_15 = 0;

        code_access.Ac = 0;
        code_access.DC = 0;
        code_access.Ex = 1;
        code_access.Pr = 1;
        code_access.Privl = 0;
        code_access.RW = 0;
        code_access.S = 1;

        code_segment.access = code_access;
        code_segment.base0_7 = 0;
        code_segment.base16_23 = 0;
        code_segment.base24_31 = 0;
        code_segment.base8_15 = 0;
        code_segment.flags = 0x0c;
        code_segment.limit0_7 = 0xffffffff & 0xff;
        code_segment.limit16_19 = SHR(0xffffffff, 16) & 0x0f;
        code_segment.limit8_15 = SHR(0xffffffff, 8)  & 0xff;

        data_access.Ac = 0;
        data_access.DC = 0;
        data_access.Ex = 0;
        data_access.Pr = 1;
        data_access.Privl = 0;
        data_access.RW = 1;
        data_access.S = 1;

        data_segment.access = data_access;
        data_segment.base0_7 = 0;
        data_segment.base16_23 = 0;
        data_segment.base24_31 = 0;
        data_segment.base8_15 = 0;
        data_segment.flags = 0x0c;
        data_segment.limit0_7 = 0xffffffff & 0xff;
        data_segment.limit16_19 = SHR(0xffffffff, 16) & 0x0f;
        data_segment.limit8_15 = SHR(0xffffffff, 8) & 0xff;

        ((S_gdt_entry *)GGDT)[0] = null_segment;
        ((S_gdt_entry *)GGDT)[1] = code_segment;
        ((S_gdt_entry *)GGDT)[2] = data_segment;

        gdt_desc.location = (uint32)GGDT;
        gdt_desc.size = sizeof(S_gdt_entry) * 3;

        load_gdt();
    }

    void load_gdt()
    {
        S_gdt_desc gdt_desc;

        gdt_desc.location = (uint32)GGDT;
        gdt_desc.size = 24;

        uint32 p = (uint32)(&gdt_desc);

        __asm__ __volatile__("lgdt (%%eax) \n" :: "a"(p));
        __asm__ __volatile__("movw $0x08, %ax \n"\
                "movw $0x10, %bx \n"\
                "mov %ax, %cs \n"\
                "mov %bx, %ds \n"\
                "mov %bx, %ss \n"\
                "mov %bx, %es \n"\
                "mov %bx, %gs \n"\
                "mov %bx, %fs \n"\
                "ljmp $0x08, $next \n"\
                "next: \n"
        );

        return;
    }
}