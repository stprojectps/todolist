/**
 * 2020-03-15
 *
 ************************************************************************
 * This header groups functions that handle some memory operation.
 */
#ifndef H__MEMOP__H
#define H__MEMOP__H

#include <string.h>

/**
 * @brief Fills firts _n bytes of memory area pointed to by _s with '\0'.
 *
 * @param [out] _s pointed memory area.
 *
 * @param [in] _n number of bytes to fill with '\0'.
 *
 * @return the memory area pointed to by _s.
 */
void* tools_memop_bzero(void *_s, const size_t _n);

/**
 * @brief Allocate memory and fill the whole content with 0x0
 *
 * @param [in] _mem_size the memory size to allocate
 *
 * @return address to the newly created memory
 */
void* new(const size_t _mem_size);

/**
 * @brief Delete memory allocated with new
 *
 * @param [out] _mem the memory to dellocate
 */
void delete (void** _mem);

#endif /* H__MEMOP__H */