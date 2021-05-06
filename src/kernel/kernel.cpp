#include "kernel/kernel.hpp"

extern "C" void kernel_main()
{
	TTY::default_char_attr = TTY_NORMAL;
	TTY::print_str("Welcome to IosifOS", TTY_NORMAL);
	TTY::print_nl(TTY_NORMAL);

	GDT::init_gdt();
	IDT::init_idt();
	Memory::init_heap();

	char *test_memory = (char *)Memory::malloc(32);
	for(uint32 i = 0; i < 32; i++)
	{
		test_memory[i] = 'a';
	}
	test_memory[31] = 0;

	TTY::print_str(test_memory, TTY_SUCCESS);
	TTY::print_nl(TTY_WARNING);
	TTY::print_str(Strings::int_to_dec(Strings::strl(test_memory)), TTY_SUCCESS);

	Memory::free(test_memory);
}