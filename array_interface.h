#ifndef ARRAY_INTERFACE_H
#define ARRAY_INTERFACE_H

#include <stdlib.h>

#include "macro.h"

typedef struct Array Array;

Array*  ArrayCreateSize(size_t length, size_t element_size);
void    ArrayDestroy(Array* array);
void*   ArrayGetData(const Array* array);
size_t  ArrayGetLength(const Array* array);
int     ArrayExpandRight(Array* array, size_t extra_length);
int     ArrayExpandLeft(Array* array, size_t extra_length);

#define ArrayCreate(type, length) ArrayCreateSize(length, sizeof(type))

#define ArrayGet(array, type, index) GET(ArrayGetData(array), type, index)

#define ArraySet(array, type, index, value) SET(ArrayGetData(array), type, index, value)

#define ArraySetCopy(array, type, index, value, copy_function) \
        ArraySet(array, type, index, function(value))

#define ArraySwap(array, type, lhs_index, rhs_index) \
        SWAP(ArrayGetData(array), type, lhs_index, rhs_index)

#define ArrayApplySlice(array, type, function, index, length) \
{ \
        type*  _data = ArrayGetData(array); \
        size_t _length = length; \
        size_t _index = index; \
        for (size_t n = _index; n < _length; n ++) \
                function(_data[n]); \
}

#define ArrayApply(array, type, function) \
        ArrayApplySlice(array, type, function, 0, ArrayGetLength(array))

#define ArrayDestroyElements(array, type, function) ArrayApply(array, type, function)

#endif