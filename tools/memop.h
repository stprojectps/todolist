/**
 * 2020-03-15
 *
 ************************************************************************
 * This header groups functions that handle some memory operation.
 */
#ifndef H__TOOLS__H
#define H__TOOLS__H

#include <string.h>

/**
 * Fills firts _n bytes of memory area pointed to by _s with '\0'.
 * @param _s: pointed memory area.
 * @param _n: number of bytes to fill with '\0'.
 * @return the memory area pointed to by _s.
 */
inline void* tools_memop_bzero(void *_s, size_t _n)
{ return memset(_s, '\0', _n); }

#endif /* H__TOOLS__H */