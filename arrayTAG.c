#include "arrayTAG.h"
#include "arrayTAG_interface.h"
#include "macros.h"

#include <stdlib.h>
#include <string.h>

ArrayTAG* ArrayCreateTAG(size_t length)
{
    ArrayTAG* array;

    array = malloc(sizeof(*array));
    CHECK_RETURN(array, NULL, NULL);

    array->data = malloc(sizeof(char*) * length);
    if (array->data == NULL)
        RETURN_AFTER(free(array), NULL);
    
    array->length = length;
    
    return array;
}

void ArrayDestroyTAG(ArrayTAG* array)
{
    free(array);
}

void ArrayDestroyDataTAG(ArrayTAG* array)
{
    free(array->data);
}

void ArrayDestroyAllTAG(ArrayTAG* array)
{
    ArrayDestroyDataTAG(array);
    ArrayDestroyTAG(array);
}

size_t ArrayLengthTAG(const ArrayTAG* array)
{
    return array->length;
}

TYPE ArrayGetTAG(const ArrayTAG* array, size_t index)
{
    return array->data[index];
}

void ArraySetTAG(ArrayTAG* array, size_t index, TYPE value)
{
    array->data[index] = value;
}

int ArrayExpandRightTAG(ArrayTAG* array, size_t extra_items)
{
    TYPE* new_data;

    new_data = realloc(array->data, (array->length + extra_items) * sizeof(TYPE));
    CHECK_RETURN(new_data, NULL, NOT_OK);

    array->data = new_data;
    array->length += extra_items;

    return OK;
}

int ArrayExpandLeftTAG(ArrayTAG* array, size_t extra_items)
{
    TYPE* new_data;

    new_data = realloc(array->data, array->length + extra_items);
    CHECK_RETURN(new_data, NULL, NOT_OK);

    memmove(new_data + extra_items, new_data, extra_items * sizeof(TYPE));
    array->data = new_data;
    array->length += extra_items;

    return OK;
}

void ArrayApplyTAG(const ArrayTAG* array, size_t index, size_t length, void (*f)(TYPE))
{
    size_t last;

    last = index + length;

    while (index < last)
    {
        f(array->data[index]);
        index ++;
    }
}