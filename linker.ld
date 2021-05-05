ENTRY(_start)
SECTIONS
{
    . = 0x0;
    .IDT BLOCK(4K):
    {
        GIDT = .;
        . += 4K;
    }
    .GDT BLOCK(4K):
    {
        GGDT = .;
        . += 4K;
    }
    .MULTIBOOT BLOCK(0x1000):
    {
        *(.multiboot)
    }
    .TEXT BLOCK(0x1000):
    {
        *(.text)
    }
    .RODATA BLOCK(0x1000):
    {
        *(.rodata)
    }
    .DATA BLOCK(0x1000):
    {
        *(.data)
    }
    .BSS BLOCK(0x1000):
    {
        *(.bss)
    }
    .STACK BLOCK(0x1000):
    {
        _stack_bottom = .;
        . += 16K;
        _stack_top = .;
    }
}