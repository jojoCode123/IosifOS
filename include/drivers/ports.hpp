#pragma once

#include "util/types.hpp"

// Write data to a port
template <typename T>
void port_out(uint16 port, T value);

// Read data from a port 
template <typename T>
T port_in(uint16 port);