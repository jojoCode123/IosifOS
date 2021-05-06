#include "lib/math.hpp"

namespace Math
{
    uint32 power(uint32 base, uint32 exponent)
    {
        if(exponent == 0)
        {
            return 1;
        }

        uint32 result = 1;
        for(uint32 i = 0; i < exponent; i++)
        {
            result *= base;
        }

        return result;
    }
}