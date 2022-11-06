#include "array_T.h"
#include "array_T_interface.h"
#include "sort_mergeTAG_interface.h"
#include "macros.h"

#include <stdlib.h>
#include <string.h>

Array_T* ArrayCreateTAG(size_t length)
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

void ArrayDestroyTAG(Array_T* array)
{
    free(array);
}

void ArrayDestroyDataTAG(Array_T* array)
{
    free(array->data);
}

void ArrayDestroyElementsTAG(Array_T* array, void (*f)(TYPE))
{
    ArrayMapTAG(array, 0, array->length, f);
}

void ArrayDestroyAllTAG(Array_T* array, void (*f)(TYPE))
{
    if (f) ArrayDestroyElementsTAG(array, f);
    ArrayDestroyDataTAG(array);
    ArrayDestroyTAG(array);
}

size_t ArrayLengthTAG(const Array_T* array)
{
    return array->length;
}

TYPE ArrayGetTAG(const Array_T* array, size_t index)
{
    return array->data[index];
}

void ArraySetTAG(Array_T* array, size_t index, TYPE value)
{
    array->data[index] = value;
}

int ArrayExpandRightTAG(Array_T* array, size_t extra_items)
{
    TYPE* new_data;

    new_data = realloc(array->data, (array->length + extra_items) * sizeof(TYPE));
    CHECK_RETURN(new_data, NULL, NOT_OK);

    array->data = new_data;
    array->length += extra_items;

    return OK;
}

int ArrayExpandLeftTAG(Array_T* array, size_t extra_items)
{
    TYPE* new_data;

    new_data = realloc(array->data, array->length + extra_items);
    CHECK_RETURN(new_data, NULL, NOT_OK);

    memmove(new_data + extra_items, new_data, extra_items * sizeof(TYPE));
    array->data = new_data;
    array->length += extra_items;

    return OK;
}

void ArrayMapTAG(const Array_T* array, size_t index, size_t length, void (*f)(TYPE))
{
    for (size_t k = index; k < length + index; k ++)
        f(array->data[k]);
}

void ArrayApplyTAG(Array_T* array, size_t index, size_t length, void (*f)(TYPE*))
{
    for (size_t k = index; k < length + index; k ++)
        f(&array->data[k]);
}

TYPE ArrayFoldTAG(const Array_T* array, size_t index, size_t length, 
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

void ArraySortSliceTAG(Array_T* array, size_t index, 
                size_t length, int (*cmp)(const TYPE, const TYPE))
{
    return MergeSortTAG(array->data, index, length, cmp);
}

void ArraySortTAG(Array_T* array, int (*cmp)(const TYPE, const TYPE))
{
    return MergeSortTAG(array->data, 0, array->length, cmp);
}