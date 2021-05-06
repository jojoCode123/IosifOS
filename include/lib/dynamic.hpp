#pragma once

#include "lib/memory.hpp"
#include "util/types.hpp"
#include "util/util.hpp"

namespace Memory
{
    namespace
    {

        struct S_block_header;
        typedef S_block_header *PS_block_header;

        struct S_header_flags;
        typedef S_header_flags *PS_header_flags;

    extern "C" S_block_header HEAP[];
        // Merge 2 free blocks together
        // Blocks are merged downwards
        bool merge(void *block);
    }

    // Allocate X bytes of memory in the heap
    // Returns a pointer to that memory, null pointer if failed
    void *malloc(size_t size);

    // Free an allocated block from the heap
    // Returns a false if failed
    bool free(void *memory);

    // Initialise the heap
    void init_heap();
}