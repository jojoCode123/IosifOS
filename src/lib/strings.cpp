#include "lib/strings.hpp"

namespace Strings
{
	STRING strc(STRING source, char *destination)
	{
		uint32 i;

		for(i = 0; source[i] != 0; i++)
		{
			destination[i] = source[i];
		}
		destination[i] = 0;

		return destination;
	}

	STRING strc_s(STRING source, char *destination, size_t size)
	{
		for(uint32 i = 0; i < size; i++)
		{
			destination[i] = source[i];
		}
		destination[size - 1] = 0;

		return destination;
	}

	size_t strl(STRING string)
	{
		size_t size;

		for(uint32 i = 0; string[i] != 0; i++)
		{
			size++;
		}

		return size;
	}
}