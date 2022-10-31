#ifndef ARRAY_INTERFACE_H
#define ARRAY_INTERFACE_H

#include <stdlib.h>

#include "macro.h"

typedef struct Array Array;

Array*  ArrayCreateSize(size_t length, size_t element_size);
void    ArrayDestroy(Array* array);
void*   ArrayGetData(const Array* array);
size_t  ArrayGetLength(const Array* array);
int     ArrayExpand(const Array* array, size_t extra_length);

#define ArrayCreate(type, length) ArrayCreateSize(length, sizeof(type))

#define ArrayGet(array, type, index) GET(ArrayGetData(array), type, index)

#define ArraySet(array, type, index, value) SET(ArrayGetData(array), type, index, value)

#define ArraySetCopy(array, type, index, value, copy_function) \
        ArraySet(array, type, index, function(value))

#define ArraySwap(array, type, lhs_index, rhs_index) \
        SWAP(ArrayGetData(array), type, lhs_index, rhs_index)

#define ArrayApply(array, type, function) \
        { \
            type* _data = ArrayGetData(array); \
            for (size_t index = 0; index < ArrayGetLength(array); index ++) \
                function(_data[index]); \
        }
#define ArrayDestroyElements(array, type, function) ArrayApply(array, type, function)

#endif