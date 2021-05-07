#include "cpu/idt.hpp"

namespace IDT
{
    S_idt_entry make_idt_entry(uint8 interrupt, void *handler, uint8 selector, uint8 type)
    {
        S_idt_entry idt_entry;

        idt_entry.offset0_15 = (uint16)((uint32)handler & 0xffff);
        idt_entry.offset16_31 = (uint16)SHR((uint32)handler & 0xffff0000, 16);
        idt_entry.selector = selector;
        idt_entry.type = type;
        idt_entry.zero = 0;

        return idt_entry;
    }

    void init_idt()
    {
        S_idt_desc idt_desc;

        init_pic(0x20, 0x28);
        for(uint32 i = 0; i < 256; i++)
        {
            GIDT[i] = make_idt_entry(i, (void *)default_handler_init, 0x08, 0x8e);
        }
        idt_desc.location = (uint32)GIDT;
        idt_desc.size = 256 * sizeof(S_idt_entry);

        GIDT[0] = make_idt_entry(0, (void *)isr0, 0x08, 0x8e);

        load_idt(&idt_desc);

        return;
    }

    void init_pic(uint8 master_pic_offset, uint8 slave_pic_offset)
    {
        uint8 pic1 = port_in<uint8>(0x21);
        uint8 pic2 = port_in<uint8>(0xa1);

        port_out<uint8>(0x21, 0xfd);
        port_out<uint8>(0xa1, 0xff);

        port_out<uint8>(0x20, 0x11);
        port_out<uint8>(0xa0, 0x11);
        port_out<uint8>(0x21, master_pic_offset);
        port_out<uint8>(0xa1, slave_pic_offset);
        port_out<uint8>(0x21, 0x04);
        port_out<uint8>(0xa1, 0x02);
        port_out<uint8>(0x21, 0x01);
        port_out<uint8>(0xa1, 0x01);

        port_out<uint8>(0x21, pic1);
        port_out<uint8>(0xa1, pic2);

        return;
    }

    void load_idt(PS_idt_desc idt_desc)
    {
        CLEAR_INTERRUPTS;
        __asm__("lidt (%%eax)" :: "a"(idt_desc));
        ENABLE_INTERRUPTS;

        return;
    }
    

    extern "C" void default_handler()
    {
        port_out<uint8>(0x20, 0x20);
        port_out<uint8>(0xa0, 0x20);
        return;
    }

    extern "C" void isr0_handler()
    {
        TTY::print_str("isr0", TTY_NORMAL);

        port_out<uint8>(0x20, 0x20);
        port_out<uint8>(0xa0, 0x20);
        return;
    }
};