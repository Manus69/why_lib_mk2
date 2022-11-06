#include "array_T.h"
#include "array_T_interface.h"
#include "sort_merge_T_interface.h"
#include "macros.h"

#include <stdlib.h>
#include <string.h>

Array_T* ArrayCreate_T(size_t length)
{
    Array_T* array;

    array = malloc(sizeof(*array));
    CHECK_RETURN(array, NULL, NULL);

    array->data = malloc(sizeof(char*) * length);
    if (array->data == NULL)
        RETURN_AFTER(free(array), NULL);
    
    array->length = length;
    
    return array;
}

void ArrayDestroy_T(Array_T* array)
{
    free(array);
}

void ArrayDestroyData_T(Array_T* array)
{
    free(array->data);
}

void ArrayDestroyElements_T(Array_T* array, void (*f)(TYPE))
{
    ArrayMap_T(array, 0, array->length, f);
}

void ArrayDestroyAll_T(Array_T* array, void (*f)(TYPE))
{
    if (f) ArrayDestroyElements_T(array, f);
    ArrayDestroyData_T(array);
    ArrayDestroy_T(array);
}

size_t ArrayLength_T(const Array_T* array)
{
    return array->length;
}

TYPE ArrayGet_T(const Array_T* array, size_t index)
{
    return array->data[index];
}

void ArraySet_T(Array_T* array, size_t index, TYPE value)
{
    array->data[index] = value;
}

int ArrayExpandRight_T(Array_T* array, size_t extra_items)
{
    TYPE* new_data;

    new_data = realloc(array->data, (array->length + extra_items) * sizeof(TYPE));
    CHECK_RETURN(new_data, NULL, NOT_OK);

    array->data = new_data;
    array->length += extra_items;

    return OK;
}

int ArrayExpandLeft_T(Array_T* array, size_t extra_items)
{
    TYPE* new_data;

    new_data = realloc(array->data, array->length + extra_items);
    CHECK_RETURN(new_data, NULL, NOT_OK);

    memmove(new_data + extra_items, new_data, extra_items * sizeof(TYPE));
    array->data = new_data;
    array->length += extra_items;

    return OK;
}

void ArrayMap_T(const Array_T* array, size_t index, size_t length, void (*f)(TYPE))
{
    for (size_t k = index; k < length + index; k ++)
        f(array->data[k]);
}

void ArrayApply_T(Array_T* array, size_t index, size_t length, void (*f)(TYPE*))
{
    for (size_t k = index; k < length + index; k ++)
        f(&array->data[k]);
}

TYPE ArrayFold_T(const Array_T* array, size_t index, size_t length, 
                TYPE (*f)(TYPE, TYPE), TYPE initial_value)
{
    TYPE result;

    result = initial_value;
    for (size_t k = index; k < length + index; k ++)
    {
        result = f(result, array->data[k]);
    }

    return result;
}

void ArraySortSlice_T(Array_T* array, size_t index, 
                size_t length, int (*cmp)(const TYPE, const TYPE))
{
    return MergeSort_T(array->data, index, length, cmp);
}

void ArraySort_T(Array_T* array, int (*cmp)(const TYPE, const TYPE))
{
    return MergeSort_T(array->data, 0, array->length, cmp);
}