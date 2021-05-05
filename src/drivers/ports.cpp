#include "drivers/ports.hpp"

template<typename T>
void port_out(uint16 port, T value)
{
    __asm__("out %%al, %%dx" : : "a"((uint8)value), "d"(port));
    return;
}

template<>
void port_out<uint8>(uint16 port, uint8 value)
{
    __asm__("out %%al, %%dx" : : "a"(value), "d"(port));
    return;
}

template<>
void port_out<uint16>(uint16 port, uint16 value)
{
    __asm__("out %%ax, %%dx" : : "a"(value), "d"(port));
    return;
}

template<>
void port_out<uint32>(uint16 port, uint32 value)
{
    __asm__("out %%eax, %%dx" : : "a"(value), "d"(port));
    return;
}

template<>
uint8 port_in(uint16 port)
{
    uint8 value;
    __asm__("in %%dx, %%al" : "=a"(value) : "d"(port));
    return value;
}

template<>
uint16 port_in(uint16 port)
{
    uint16 value;
    __asm__ __volatile__("in %%dx, %%ax" : "=a"(value) : "d"(port));
    return value;
}

template<>
uint32 port_in(uint16 port)
{
    uint32 value;
    __asm__ __volatile__("in %%dx, %%eax" : "=a"(value) : "d"(port));
    return value;
}