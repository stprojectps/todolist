#include <stdlib.h>

#include "memop.h"

void* tools_memop_bzero(void *_s, const size_t _n)
{
    return memset(_s, '\0', _n);
}

void* new(const size_t _mem_size)
{
    void* new_mem = malloc(_mem_size);
    tools_memop_bzero(new_mem, _mem_size);
    return new_mem;
}

void delete(void** _mem)
{
    free(*_mem);
    *_mem = NULL;
}