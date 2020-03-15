#include "memop.h"

void* tools_memop_bzero(void *_s, size_t _n)
{
    return memset(_s, '\0', _n);
}