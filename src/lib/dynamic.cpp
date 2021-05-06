#include "lib/dynamic.hpp"

namespace Memory
{
    namespace
    {
        struct S_header_flags
        {
            uint8 is_free:1;
            uint8 is_first:1;
            uint8 is_last:1;
            uint8 __padding:5;
            uint8 __padding_;
            uint16 __padding__;
        };

        struct S_block_header
        {
            PS_block_header p_previous_header;
            PS_block_header p_next_header;
            uint32 size;
            S_header_flags flags;
        };

        // Merge 2 free blocks together
        // Blocks are merged downwards
        bool merge(void *block)
        {
            PS_block_header header = (PS_block_header)block;

            if(!header->flags.is_free || header->flags.is_last || !header->p_next_header->flags.is_free)
            {
                return false;
            }

            header->flags = header->p_next_header->flags;
            header->size += header->p_next_header->size + sizeof(S_block_header);
            header->p_next_header = header->p_next_header->p_next_header;

            return true;
        }
    }

    void *malloc(size_t size)
    {
        PS_block_header current_header = (PS_block_header)HEAP;

        while(true)
        {
            PS_block_header header = current_header;

            if(!header->flags.is_free)
            {
                if(header->flags.is_last) return nullptr;

                current_header = header->p_next_header;
            }
            else
            {
                if(header->flags.is_last)
                {
                    if(header->size < size + sizeof(S_block_header)) return nullptr;
                }

                if(header->size < size + sizeof(S_block_header))
                {
                    current_header = header->p_next_header;
                }
                else if(header->size == size)
                {
                    header->flags.is_free = 0;
                    return (void *)(header + sizeof(S_block_header));
                }
                else
                {
                    PS_block_header next_header = (PS_block_header)(header + size + sizeof(S_block_header));
                    if(header->flags.is_last)
                    {
                        next_header->flags.is_last = 1;
                        next_header->p_next_header = 0;
                        header->flags.is_last = 0;
                    }
                    else
                    {
                        header->p_next_header->p_previous_header = next_header;
                    }
                    next_header->flags.is_first = 0;
                    next_header->flags.is_free = 1;
                    next_header->size = header->size - (size + sizeof(S_block_header));
                    next_header->p_next_header = header->p_next_header;
                    next_header->p_previous_header = header;
                    
                    header->p_next_header = next_header;
                    header->size = size;
                    header->flags.is_free = 0;

                    return (void *)(header + sizeof(S_block_header));
                }
            }
        }
    }

    bool free(void *memory)
    {
        PS_block_header header = (PS_block_header)((uint8 *)memory - sizeof(S_block_header));

        if(header->p_previous_header->flags.is_free && header->p_next_header->flags.is_free)
        {
            merge(header);
            merge(header->p_previous_header);
            return true;
        }
        else if(header->p_next_header->flags.is_free)
        {
            merge(header);
            return true;
        }
        else if(header->p_previous_header->flags.is_free)
        {
            merge(header->p_previous_header);
            return true;
        }
        else
        {
            header->flags.is_free = 0;
            return true;
        }
    }

    void init_heap()
    {
        uint32 heap_size = 1048576;

        PS_block_header first_block = (S_block_header *)HEAP;

        first_block->flags.is_first = 1;
        first_block->flags.is_last = 1;
        first_block->flags.is_free = 1;

        first_block->p_next_header = 0;
        first_block->p_previous_header = 0;
        first_block->size = heap_size - sizeof(S_block_header);
    }
}