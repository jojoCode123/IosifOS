#include "lib/memory.hpp"

namespace Memory
{
    template <typename T>
    T *memc(T *source, T *destination, size_t size)
    {
        for(uint32 i = 0; i < size; i++)
        {
            destination[i] = source[i];
        }

        return destination;
    }

    template <>
    ushort *memc(ushort *source, ushort *destination, size_t size)
    {
        for(uint32 i = 0; i < size; i++)
        {
            destination[i] = source[i];
        }

        return destination;
    }

    template <>
    char *memc(char *source, char *destination, size_t size)
    {
        for(uint32 i = 0; i < size; i++)
        {
            destination[i] = source[i];
        }

        return destination;
    }

    template <typename T>
    T *mems(T *memory, T value, size_t size)
    {
        for(uint32 i = 0; i < size; i++)
        {
            memory[i] = value;
        }

        return memory;
    }

    template <>
    ushort *mems<ushort>(ushort *memory, ushort value, size_t size)
    {
        for(uint32 i = 0; i < size; i++)
        {
            memory[i] = value;
        }

        return memory;
    }
}