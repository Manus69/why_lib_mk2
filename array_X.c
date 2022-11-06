#include "array_X.h"
#include "array_X_interface.h"
#include "sort_merge_X_interface.h"
#include "macros.h"

#include <stdlib.h>
#include <string.h>

Array_X* ArrayCreate_X(size_t length)
{
    Array_X* array;

    array = malloc(sizeof(*array));
    CHECK_RETURN(array, NULL, NULL);

    array->data = malloc(sizeof(char*) * length);
    if (array->data == NULL)
        RETURN_AFTER(free(array), NULL);
    
    array->length = length;
    
    return array;
}

Array_X* ArrayCreateZero_X(size_t length)
{
    Array_X* array;

    array = ArrayCreate_X(length);
    CHECK_RETURN(array, NULL, NULL);

    memset(array->data, 0, array->length * sizeof(XYPE));

    return array;
}

void ArrayDestroy_X(Array_X* array)
{
    free(array);
}

void ArrayDestroyData_X(Array_X* array)
{
    free(array->data);
}

void ArrayDestroyElements_X(Array_X* array, void (*f)(XYPE))
{
    ArrayMap_X(array, 0, array->length, f);
}

void ArrayDestroyAll_X(Array_X* array, void (*f)(XYPE))
{
    if (f) ArrayDestroyElements_X(array, f);
    ArrayDestroyData_X(array);
    ArrayDestroy_X(array);
}

size_t ArrayLength_X(const Array_X* array)
{
    return array->length;
}

XYPE ArrayGet_X(const Array_X* array, size_t index)
{
    return array->data[index];
}

void ArraySet_X(Array_X* array, size_t index, XYPE value)
{
    array->data[index] = value;
}

int ArrayExpandRight_X(Array_X* array, size_t extra_items)
{
    XYPE* new_data;

    new_data = realloc(array->data, (array->length + extra_items) * sizeof(XYPE));
    CHECK_RETURN(new_data, NULL, NOT_OK);

    array->data = new_data;
    array->length += extra_items;

    return OK;
}

int ArrayExpandLeft_X(Array_X* array, size_t extra_items)
{
    XYPE* new_data;

    new_data = realloc(array->data, array->length + extra_items);
    CHECK_RETURN(new_data, NULL, NOT_OK);

    memmove(new_data + extra_items, new_data, extra_items * sizeof(XYPE));
    array->data = new_data;
    array->length += extra_items;

    return OK;
}

void ArrayMap_X(const Array_X* array, size_t index, size_t length, void (*f)(XYPE))
{
    for (size_t k = index; k < length + index; k ++)
        f(array->data[k]);
}

void ArrayApply_X(Array_X* array, size_t index, size_t length, void (*f)(XYPE*))
{
    for (size_t k = index; k < length + index; k ++)
        f(&array->data[k]);
}

XYPE ArrayFold_X(const Array_X* array, size_t index, size_t length, 
                XYPE (*f)(XYPE, XYPE), XYPE initial_value)
{
    XYPE result;

    result = initial_value;
    for (size_t k = index; k < length + index; k ++)
    {
        result = f(result, array->data[k]);
    }

    return result;
}

void ArraySortSlice_X(Array_X* array, size_t index, 
                size_t length, int (*cmp)(const XYPE, const XYPE))
{
    return MergeSort_X(array->data, index, length, cmp);
}

void ArraySort_X(Array_X* array, int (*cmp)(const XYPE, const XYPE))
{
    return MergeSort_X(array->data, 0, array->length, cmp);
}