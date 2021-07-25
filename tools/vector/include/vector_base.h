/**
 * @file vector_base.h
 *
 * @author Pape Moussa SARR
 *
 * @brief 
 *
 * @version 0.1
 *
 * @date 2021-07-24
 *
 * @copyright NO LICENSE
 *
 */

#ifndef VECTOR_BASE_H_
#define VECTOR_BASE_H_

#include <stdint.h>

/* Maximunm size of a vector */
#define VECTOR_MAX_SIZE = 8192;

/**
 * @brief 
 */
typedef enum VECTOR_TYPE_e
{
    POINTER,    ///
    VALUE       ///
} VECTOR_TYPE_e;

/**
 * @brief Definition of vector
 */
typedef struct vector_t
{
    uint32_t    size;       /* size of the vector */
    uint32_t    capacity;   /* capacity of the vector */
    void*       index;      /* storage */
} vector_t;



#endif /* VECTOR_BASE_H_ */