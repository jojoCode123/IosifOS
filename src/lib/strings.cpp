#include "lib/strings.hpp"

namespace Strings
{
	const char *strc(const char *source, char *destination)
	{
		uint32 i;

		for(i = 0; source[i] != 0; i++)
		{
			destination[i] = source[i];
		}
		destination[i] = 0;

		return destination;
	}

	const char *strc_s(const char *source, char *destination, size_t size)
	{
		for(uint32 i = 0; i < size; i++)
		{
			destination[i] = source[i];
		}
		destination[size - 1] = 0;

		return destination;
	}

	size_t strl(const char *string)
	{
		size_t size = 0;

		while(string[size] != 0)
		{
			size++;
		}

		return size;
	}

	bool strcmp_complete(const char *string1, const char *string2)
	{
		size_t length_string1 = strl(string1);
		size_t length_string2 = strl(string2);

		if(length_string1 != length_string2)
		{
			return false;
		}

		for(uint32 i = 0; i < length_string1; i++)
		{
			if(string1[i] != string2[i])
			{
				return false;
			}
		}
		return true;
	}

	bool strcmp_partial(const char *string1, const char *string2, size_t length)
	{
		size_t length_string1 = strl(string1);
		size_t length_string2 = strl(string2);

		if(length >= length_string1 || length >= length_string2)
		{
			return strcmp_complete(string1, string2);
		}

		for(uint32 i = 0; i < length; i++)
		{
			if(string1[i] != string2[i])
			{
				return false;
			}
		}

		return true;
	}

	uint32 remove_whitespace(char *string, size_t length = NULL)
	{
		uint32 whitespaces = 0;

		if(!length)
		{
			length = strl(string);
		}

		for(uint32 i = 0; i < length; i++)
		{
			if(string[i] == ' ')
			{
				whitespaces++;
				Memory::memc<char>(string+i+1, string+i, length-i-1);
				i--;
			}
		}
		string[length-whitespaces] = 0;
		return whitespaces;
	}

	char byte_to_ascii(uint8 byte)
	{
		byte &= 0x0f;
		if(byte <= 0x09)
		{
			byte += 0x30;
		}
		else
		{
			byte += 0x57;
		}

		return (char)byte;
	}

	uint8 ascii_to_byte(char digit)
	{
		if(digit >= 0x30 && digit <= 0x39)
		{
			digit -= 0x30;
		}
		else if(digit >= 0x61 && digit <= 0x66)
		{
			digit -= 0x57;
		}
		else
		{
			return 0x10;
		}

		return (uint8)digit;
	}

	const char *byte_to_hex(uint8 byte)
	{
		static char output[3];
		
		uint8 low = LOW(byte);
		uint8 high = HIGH(byte);

		output[0] = byte_to_ascii(high);
		output[1] = byte_to_ascii(low);
		output[2] = 0;

		return output;
	}

	const char *bytes_to_hex(uint8 *bytes, char output[], size_t length)
	{
		for(uint32 i = 0; i < length; i++)
		{
			strc(byte_to_hex(bytes[i]), &output[2*i]);
		}

		return (const char *)output;
	}

	uint8 hex_to_byte(const char *hex)
	{
		uint8 high = ascii_to_byte(hex[0]);
		uint8 low = ascii_to_byte(hex[1]);

		return SHL(high, 4) + low;
	}

	const char *int_to_dec(uint32 value)
	{
		static char output[11];

		if(value == 0)
		{
			output[0] = '0';
			output[1] = 0;
			return output;
		}

		size_t size_of_output;
		uint32 temp = value;
		for(size_of_output = 0; temp != 0; size_of_output++)
		{
			temp /= 10;
		}

		uint8 digit;
		uint32 previous_operand = 0;

		for(uint32 i = 0; i < size_of_output; i++)
		{
			digit = ((value - previous_operand) / Math::power(10, i)) % 10;
			previous_operand += digit * Math::power(10, i);
			output[size_of_output-1-i] = byte_to_ascii(digit);
		}
		output[size_of_output] = 0;

		return output;
	}

	const char *int_to_hex(uint32 value)
	{
		static char output[9];

		if(value == 0)
		{
			strc("00", output);
			return output;
		}

		size_t size_of_output;
		uint32 temp = value;
		for(size_of_output = 0; temp != 0; size_of_output++)
		{
			temp /= 0x10;
		}

		uint8 digit;
		uint32 previous_operand = 0;

		for(uint32 i = 0; i < size_of_output; i++)
		{
			digit = ((value - previous_operand) / Math::power(0x10, i)) & 0x10;
			previous_operand += digit * Math::power(0x10, i);
			output[size_of_output-i-1] = byte_to_ascii(digit);
		}
		output[size_of_output] = 0;

		return output;
	}

	uint32 dec_to_int(const char *decimal)
	{
		size_t size = strl(decimal);
		uint32 result = 0;

		for(uint32 i = 0; i < size; i++)
		{
			uint8 digit = ascii_to_byte(decimal[i]);
			result += digit * Math::power(10, size-i-1);
		}

		return result;
	}

	uint32 hex_to_int(const char *hex)
	{
		size_t size = strl(hex);
		uint32 result = 0;

		if(size == 0)
		{
			return 0;
		}

		for(uint32 i = 0; i < size; i++)
		{
			uint8 digit = ascii_to_byte(hex[i]);
			result += digit * Math::power(0x10, size-i-1);
		}

		return result;
	}
}