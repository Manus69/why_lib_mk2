#include "array_STR.h"
#include "array_STR_interface.h"
#include "sort_merge_STR_interface.h"
#include "macros.h"

#include <stdlib.h>
#include <string.h>

Array_STR* ArrayCreate_STR(size_t length)
{
    Array_STR* array;

    array = malloc(sizeof(*array));
    CHECK_RETURN(array, NULL, NULL);

    array->data = malloc(sizeof(char*) * length);
    if (array->data == NULL)
        RETURN_AFTER(free(array), NULL);
    
    array->length = length;
    
    return array;
}

Array_STR* ArrayCreateZero_STR(size_t length)
{
    Array_STR* array;

    array = ArrayCreate_STR(length);
    CHECK_RETURN(array, NULL, NULL);

    memset(array->data, 0, array->length * sizeof(char*));

    return array;
}

void ArrayDestroy_STR(Array_STR* array)
{
    free(array);
}

void ArrayDestroyData_STR(Array_STR* array)
{
    free(array->data);
}

void ArrayDestroyElements_STR(Array_STR* array, void (*f)(char*))
{
    ArrayMap_STR(array, 0, array->length, f);
}

void ArrayDestroyAll_STR(Array_STR* array, void (*f)(char*))
{
    if (f) ArrayDestroyElements_STR(array, f);
    ArrayDestroyData_STR(array);
    ArrayDestroy_STR(array);
}

size_t ArrayLength_STR(const Array_STR* array)
{
    return array->length;
}

char* ArrayGet_STR(const Array_STR* array, size_t index)
{
    return array->data[index];
}

void ArraySet_STR(Array_STR* array, size_t index, char* value)
{
    array->data[index] = value;
}

int ArrayExpandRight_STR(Array_STR* array, size_t extra_items)
{
    char** new_data;

    new_data = realloc(array->data, (array->length + extra_items) * sizeof(char*));
    CHECK_RETURN(new_data, NULL, NOT_OK);

    array->data = new_data;
    array->length += extra_items;

    return OK;
}

int ArrayExpandLeft_STR(Array_STR* array, size_t extra_items)
{
    char** new_data;

    new_data = realloc(array->data, array->length + extra_items);
    CHECK_RETURN(new_data, NULL, NOT_OK);

    memmove(new_data + extra_items, new_data, extra_items * sizeof(char*));
    array->data = new_data;
    array->length += extra_items;

    return OK;
}

void ArrayMap_STR(const Array_STR* array, size_t index, size_t length, void (*f)(char*))
{
    for (size_t k = index; k < length + index; k ++)
        f(array->data[k]);
}

void ArrayApply_STR(Array_STR* array, size_t index, size_t length, void (*f)(char**))
{
    for (size_t k = index; k < length + index; k ++)
        f(&array->data[k]);
}

char* ArrayFold_STR(const Array_STR* array, size_t index, size_t length, 
                char* (*f)(char*, char*), char* initial_value)
{
    char* result;

    result = initial_value;
    for (size_t k = index; k < length + index; k ++)
    {
        result = f(result, array->data[k]);
    }

    return result;
}

void ArraySortSlice_STR(Array_STR* array, size_t index, 
                size_t length, int (*cmp)(const char*, const char*))
{
    return MergeSort_STR(array->data, index, length, cmp);
}

void ArraySort_STR(Array_STR* array, int (*cmp)(const char*, const char*))
{
    return MergeSort_STR(array->data, 0, array->length, cmp);
}