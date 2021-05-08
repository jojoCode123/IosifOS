#include "kernel/kernel.hpp"

void initialise_stuff()
{
	GDT::init_gdt();
	IDT::init_idt();
	Memory::init_heap();

	return;
}

extern "C" void kernel_main()
{
	initialise_stuff();

	TTY::default_char_attr = TTY_NORMAL;

	TTY::print_str("Welcome to IosifOS!\n", TTY_NORMAL);

	char input[500];

	const char *help_menu = "\nIosifOS help manual:\n\n"
	"\thelp - print this help screen\n"
	"\tclear - clear the screen\n"
	"\n";

	const char *error_msg = "Invalid command re.\nType \"help\" for help.\n";

	while(true)
	{
		TTY::print_str("iosifshell> ");
		Keyboard::read(input, 500, '\n');
		if(Strings::strcmp_complete("clear", input))
		{
			TTY::clear_screen(true);
		}
		else if(Strings::strcmp_complete("help", input))
		{
			TTY::print_str(help_menu);
		}
		else if(Strings::strcmp_complete("\n", input))
		{
			continue;
		}
		else
		{
			TTY::print_str(error_msg, TTY_WARNING);
		}
	}
}