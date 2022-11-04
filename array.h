#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

#include "macros.h"

typedef struct Array Array;

struct Array
{
    void*   data;
    size_t  length;
    size_t  element_size;
};

void    ArrayInit(Array* array, void* data, size_t length, size_t element_size);
Array*  ArrayCreate(size_t length, size_t element_size);
void    ArrayDestroy(Array* array);
size_t  ArrayLength(const Array* array);
int     ArrayExpandRight(Array* array, size_t n_elements);
void*   ArrayGetPtr(const Array* array, size_t index);
#define ArraySet(array, type, index, value) \
    SET(array->data, type, index, value)

#define GetArrayDeclarations(type, name) \
type    ArrayGet##name(const Array* array, size_t index); \
void    ArraySet##name(Array* array, size_t index, type value); \
Array*  ArrayCreate##name(size_t length);\

#define GetArrayDefinitions(type, name) \
type ArrayGet##name(const Array* array, size_t index)\
{ \
    return GET(array->data, type, index); \
} \
\
void ArraySet##name(Array* array, size_t index, type value) \
{ \
    SET(array->data, type, index, value); \
} \
\
Array* ArrayCreate##name(size_t length) \
{ \
    return ArrayCreate(length, sizeof(type)); \
}

#endif