#ifndef ARRAY_INTERFACE_H
#define ARRAY_INTERFACE_H

#include <stdlib.h>

#include "macro.h"
#include "array.h"

typedef struct Array Array;

Array*  ArrayCreateSize(size_t length, size_t element_size);
void    ArrayDestroy(Array* array);
void*   ArrayGetData(const Array* array);
size_t  ArrayGetLength(const Array* array);
int     ArrayExpandRight(Array* array, size_t extra_length);
int     ArrayExpandLeft(Array* array, size_t extra_length);

#define ArrayCreate(_type, _length) ArrayCreateSize(_length, sizeof(_type))

#define ArrayGet(_array, _type, index) GET(_array->data, _type, index)

#define ArraySet(_array, _type, _index, _value) SET(_array->data, _type, _index, _value)

#define ArraySetCopy(_array, _type, _index, _value, _function) \
        ArraySet(_array, _type, _index, _function(value))

#define ArraySwap(_array, _type, _lhs_index, _rhs_index) \
        SWAP(_array->data, _type, _lhs_index, _rhs_index)

#define ArrayApplySlice(_array, _type, _function, _index, _length) \
{ \
        type*  __data = _array->data; \
        size_t __len = _length; \
        size_t __index = _index; \
        \
        for (size_t n = __index; n < __len; n ++) \
                function(__data[n]); \
}

#define ArrayApply(_array, _type, _function) \
        ArrayApplySlice(_array, _type, _function, 0, _array->length)

#define ArrayFoldSlice(_array, _type, _function, _target, _initial_value, _index, _length) \
{ \
        type*   __data = _array->data; \
        type    __value = _initial_value; \
        size_t  __index = _index; \
        size_t  __len = _length; \
        \
        for (size_t n = __index; n < __len; n ++) \
                __value = function(__value, __data[n]); \
        \
        _target = __value; \
}

#define ArrayFold(_array, _type, _function, _target, _initial_value) \
        ArrayFoldSlice(_array, _type, _function, _target, _initial_value, 0, _array->length)

#define ArrayDestroyElements(_array, _type, _function) ArrayApply(_array, _type, _function)

#endif