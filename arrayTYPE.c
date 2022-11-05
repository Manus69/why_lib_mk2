#include "arrayTYPE.h"
#include "arrayTYPE_interface.h"
#include "macros.h"

#include <stdlib.h>

ArrayTAG* ArrayCreateTAG(size_t length)
{
    ArrayTAG* array;

    array = malloc(sizeof(*array));
    CHECK_RETURN(array, NULL, NULL);

    array->data = malloc(sizeof(TYPE) * length);
    if (array->data == NULL)
        RETURN_AFTER(free(array), NULL);
    
    array->length = length;
    
    return array;
}

void ArrayDestroyTAG(ArrayTAG* array)
{
    free(array);
}

void ArrayDestroyData(ArrayTAG* array)
{
    free(array->data);
}

void ArrayDestroyAllTAG(ArrayTAG* array)
{
    ArrayDestroyData(array);
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