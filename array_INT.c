#include "array_INT.h"
#include "array_INT_interface.h"
#include "sort_merge_INT.h"
#include "macros.h"

#include <stdlib.h>
#include <string.h>

Array_INT* ArrayCreate_INT(size_t length)
{
    Array_INT* array;

    array = malloc(sizeof(*array));
    CHECK_RETURN(array, NULL, NULL);

    array->data = malloc(sizeof(char*) * length);
    if (array->data == NULL)
        RETURN_AFTER(free(array), NULL);
    
    array->length = length;
    
    return array;
}

Array_INT* ArrayCreateZero_INT(size_t length)
{
    Array_INT* array;

    array = ArrayCreate_INT(length);
    CHECK_RETURN(array, NULL, NULL);

    memset(array->data, 0, array->length * sizeof(int));

    return array;
}

void ArrayDestroy_INT(Array_INT* array)
{
    free(array);
}

void ArrayDestroyData_INT(Array_INT* array)
{
    free(array->data);
}

void ArrayDestroyElements_INT(Array_INT* array, void (*f)(int))
{
    ArrayMap_INT(array, 0, array->length, f);
}

void ArrayDestroyAll_INT(Array_INT* array, void (*f)(int))
{
    if (f) ArrayDestroyElements_INT(array, f);
    ArrayDestroyData_INT(array);
    ArrayDestroy_INT(array);
}

size_t ArrayLength_INT(const Array_INT* array)
{
    return array->length;
}

int ArrayGet_INT(const Array_INT* array, size_t index)
{
    return array->data[index];
}

void ArraySet_INT(Array_INT* array, size_t index, int value)
{
    array->data[index] = value;
}

int ArrayExpandRight_INT(Array_INT* array, size_t extra_items)
{
    int* new_data;

    new_data = realloc(array->data, (array->length + extra_items) * sizeof(int));
    CHECK_RETURN(new_data, NULL, NOT_OK);

    array->data = new_data;
    array->length += extra_items;

    return OK;
}

int ArrayExpandLeft_INT(Array_INT* array, size_t extra_items)
{
    int* new_data;

    new_data = realloc(array->data, array->length + extra_items);
    CHECK_RETURN(new_data, NULL, NOT_OK);

    memmove(new_data + extra_items, new_data, extra_items * sizeof(int));
    array->data = new_data;
    array->length += extra_items;

    return OK;
}

void ArrayMap_INT(const Array_INT* array, size_t index, size_t length, void (*f)(int))
{
    for (size_t k = index; k < length + index; k ++)
        f(array->data[k]);
}

void ArrayApply_INT(Array_INT* array, size_t index, size_t length, void (*f)(int*))
{
    for (size_t k = index; k < length + index; k ++)
        f(&array->data[k]);
}

int ArrayFold_INT(const Array_INT* array, size_t index, size_t length, 
                int (*f)(int, int), int initial_value)
{
    int result;

    result = initial_value;
    for (size_t k = index; k < length + index; k ++)
    {
        result = f(result, array->data[k]);
    }

    return result;
}

void ArraySortSlice_INT(Array_INT* array, size_t index, 
                size_t length, int (*cmp)(const int, const int))
{
    return MergeSort_INT(array->data, index, length, cmp);
}

void ArraySort_INT(Array_INT* array, int (*cmp)(const int, const int))
{
    return MergeSort_INT(array->data, 0, array->length, cmp);
}

size_t ArrayFindIndex_INT(const Array_INT* array, int value,
                size_t index, size_t length, int (*cmp)(const int, const int))
{
    while (index < length)
    {
        CHECK_RETURN(cmp(array->data[index], value), 0, index);
        index ++;
    }

    return -1;
}