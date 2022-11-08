#include "array_VX.h"
#include "array_VX_interface.h"
#include "sort_merge_VX.h"
#include "macros.h"

#include <stdlib.h>
#include <string.h>

Array_VX* ArrayCreate_VX(size_t length)
{
    Array_VX* array;

    array = malloc(sizeof(*array));
    CHECK_RETURN(array, NULL, NULL);

    array->data = malloc(sizeof(char*) * length);
    if (array->data == NULL)
        RETURN_AFTER(free(array), NULL);
    
    array->length = length;
    
    return array;
}

Array_VX* ArrayCreateZero_VX(size_t length)
{
    Array_VX* array;

    array = ArrayCreate_VX(length);
    CHECK_RETURN(array, NULL, NULL);

    memset(array->data, 0, array->length * sizeof(Vector_X*));

    return array;
}

void ArrayDestroy_VX(Array_VX* array)
{
    free(array);
}

void ArrayDestroyData_VX(Array_VX* array)
{
    free(array->data);
}

void ArrayDestroyElements_VX(Array_VX* array, void (*f)(Vector_X*))
{
    ArrayMap_VX(array, 0, array->length, f);
}

void ArrayDestroyAll_VX(Array_VX* array, void (*f)(Vector_X*))
{
    if (f) ArrayDestroyElements_VX(array, f);
    ArrayDestroyData_VX(array);
    ArrayDestroy_VX(array);
}

size_t ArrayLength_VX(const Array_VX* array)
{
    return array->length;
}

Vector_X* ArrayGet_VX(const Array_VX* array, size_t index)
{
    return array->data[index];
}

void ArraySet_VX(Array_VX* array, size_t index, Vector_X* value)
{
    array->data[index] = value;
}

int ArrayExpandRight_VX(Array_VX* array, size_t extra_items)
{
    Vector_X** new_data;

    new_data = realloc(array->data, (array->length + extra_items) * sizeof(Vector_X*));
    CHECK_RETURN(new_data, NULL, NOT_OK);

    array->data = new_data;
    array->length += extra_items;

    return OK;
}

int ArrayExpandLeft_VX(Array_VX* array, size_t extra_items)
{
    Vector_X** new_data;

    new_data = realloc(array->data, array->length + extra_items);
    CHECK_RETURN(new_data, NULL, NOT_OK);

    memmove(new_data + extra_items, new_data, extra_items * sizeof(Vector_X*));
    array->data = new_data;
    array->length += extra_items;

    return OK;
}

void ArrayMap_VX(const Array_VX* array, size_t index, size_t length, void (*f)(Vector_X*))
{
    for (size_t k = index; k < length + index; k ++)
        f(array->data[k]);
}

void ArrayApply_VX(Array_VX* array, size_t index, size_t length, void (*f)(Vector_X**))
{
    for (size_t k = index; k < length + index; k ++)
        f(&array->data[k]);
}

Vector_X* ArrayFold_VX(const Array_VX* array, size_t index, size_t length, 
                Vector_X* (*f)(Vector_X*, Vector_X*), Vector_X* initial_value)
{
    Vector_X* result;

    result = initial_value;
    for (size_t k = index; k < length + index; k ++)
    {
        result = f(result, array->data[k]);
    }

    return result;
}

void ArraySortSlice_VX(Array_VX* array, size_t index, 
                size_t length, int (*cmp)(const Vector_X*, const Vector_X*))
{
    return MergeSort_VX(array->data, index, length, cmp);
}

void ArraySort_VX(Array_VX* array, int (*cmp)(const Vector_X*, const Vector_X*))
{
    return MergeSort_VX(array->data, 0, array->length, cmp);
}

size_t ArrayFindIndex_VX(const Array_VX* array, Vector_X* value,
                size_t index, size_t length, int (*cmp)(const Vector_X*, const Vector_X*))
{
    while (index < length)
    {
        CHECK_RETURN(cmp(array->data[index], value), 0, index);
        index ++;
    }

    return -1;
}