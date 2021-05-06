#pragma once

#include "util/types.hpp"

#define TRUE 1
#define FALSE 0
#define NULL 0

#define LOW(x) (0x0f & x)
#define HIGH(x) ((0xf0 & x) >> 4)

#define ADD(x, y) ((x) + (y))
#define SUB(x, y) ((x) - (y))
#define MUL(x, y) ((x) * (y))
#define DIV(x, y) ((x) / (y))
#define MOD(x, y) ((x) % (y))
#define SHL(x, y) ((x) << (y))
#define SHR(x, y) ((x) >> (y))