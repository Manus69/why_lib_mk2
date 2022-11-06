#include "array_PTR.h"
#include "array_PTR_interface.h"
#include "sort_merge_PTR_interface.h"
#include "macros.h"

#include <stdlib.h>
#include <string.h>

Array_PTR* ArrayCreate_PTR(size_t length)
{
    Array_PTR* array;

    array = malloc(sizeof(*array));
    CHECK_RETURN(array, NULL, NULL);

    array->data = malloc(sizeof(char*) * length);
    if (array->data == NULL)
        RETURN_AFTER(free(array), NULL);
    
    array->length = length;
    
    return array;
}

Array_PTR* ArrayCreateZero_PTR(size_t length)
{
    Array_PTR* array;

    array = ArrayCreate_PTR(length);
    CHECK_RETURN(array, NULL, NULL);

    memset(array->data, 0, array->length * sizeof(void*));

    return array;
}

void ArrayDestroy_PTR(Array_PTR* array)
{
    free(array);
}

void ArrayDestroyData_PTR(Array_PTR* array)
{
    free(array->data);
}

void ArrayDestroyElements_PTR(Array_PTR* array, void (*f)(void*))
{
    ArrayMap_PTR(array, 0, array->length, f);
}

void ArrayDestroyAll_PTR(Array_PTR* array, void (*f)(void*))
{
    if (f) ArrayDestroyElements_PTR(array, f);
    ArrayDestroyData_PTR(array);
    ArrayDestroy_PTR(array);
}

size_t ArrayLength_PTR(const Array_PTR* array)
{
    return array->length;
}

void* ArrayGet_PTR(const Array_PTR* array, size_t index)
{
    return array->data[index];
}

void ArraySet_PTR(Array_PTR* array, size_t index, void* value)
{
    array->data[index] = value;
}

int ArrayExpandRight_PTR(Array_PTR* array, size_t extra_items)
{
    void** new_data;

    new_data = realloc(array->data, (array->length + extra_items) * sizeof(void*));
    CHECK_RETURN(new_data, NULL, NOT_OK);

    array->data = new_data;
    array->length += extra_items;

    return OK;
}

int ArrayExpandLeft_PTR(Array_PTR* array, size_t extra_items)
{
    void** new_data;

    new_data = realloc(array->data, array->length + extra_items);
    CHECK_RETURN(new_data, NULL, NOT_OK);

    memmove(new_data + extra_items, new_data, extra_items * sizeof(void*));
    array->data = new_data;
    array->length += extra_items;

    return OK;
}

void ArrayMap_PTR(const Array_PTR* array, size_t index, size_t length, void (*f)(void*))
{
    for (size_t k = index; k < length + index; k ++)
        f(array->data[k]);
}

void ArrayApply_PTR(Array_PTR* array, size_t index, size_t length, void (*f)(void**))
{
    for (size_t k = index; k < length + index; k ++)
        f(&array->data[k]);
}

void* ArrayFold_PTR(const Array_PTR* array, size_t index, size_t length, 
                void* (*f)(void*, void*), void* initial_value)
{
    void* result;

    result = initial_value;
    for (size_t k = index; k < length + index; k ++)
    {
        result = f(result, array->data[k]);
    }

    return result;
}

void ArraySortSlice_PTR(Array_PTR* array, size_t index, 
                size_t length, int (*cmp)(const void*, const void*))
{
    return MergeSort_PTR(array->data, index, length, cmp);
}

void ArraySort_PTR(Array_PTR* array, int (*cmp)(const void*, const void*))
{
    return MergeSort_PTR(array->data, 0, array->length, cmp);
}

size_t ArrayFindIndex_PTR(const Array_PTR* array, void* value,
                size_t index, size_t length, int (*cmp)(const void*, const void*))
{
    while (index < length)
    {
        CHECK_RETURN(cmp(array->data[index], value), 0, index);
        index ++;
    }

    return -1;
}