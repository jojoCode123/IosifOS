#pragma once

#include "util/types.hpp"

namespace Memory
{
	template <typename T>
	T *memc(T *source, T *destination, size_t size);

	template <typename T>
	T *mems(T *memory, T value, size_t size);
}