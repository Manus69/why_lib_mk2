#include "arrayCHARPTR.h"
#include "arrayCHARPTR_interface.h"
#include "macros.h"

#include <stdlib.h>
#include <string.h>

ArrayCHARPTR* ArrayCreateCHARPTR(size_t length)
{
    ArrayCHARPTR* array;

    array = malloc(sizeof(*array));
    CHECK_RETURN(array, NULL, NULL);

    array->data = malloc(sizeof(char*) * length);
    if (array->data == NULL)
        RETURN_AFTER(free(array), NULL);
    
    array->length = length;
    
    return array;
}

void ArrayDestroyCHARPTR(ArrayCHARPTR* array)
{
    free(array);
}

void ArrayDestroyDataCHARPTR(ArrayCHARPTR* array)
{
    free(array->data);
}

void ArrayDestroyAllCHARPTR(ArrayCHARPTR* array)
{
    ArrayDestroyDataCHARPTR(array);
    ArrayDestroyCHARPTR(array);
}

size_t ArrayLengthCHARPTR(const ArrayCHARPTR* array)
{
    return array->length;
}

char* ArrayGetCHARPTR(const ArrayCHARPTR* array, size_t index)
{
    return array->data[index];
}

void ArraySetCHARPTR(ArrayCHARPTR* array, size_t index, char* value)
{
    array->data[index] = value;
}

int ArrayExpandRightCHARPTR(ArrayCHARPTR* array, size_t extra_items)
{
    char** new_data;

    new_data = realloc(array->data, (array->length + extra_items) * sizeof(char*));
    CHECK_RETURN(new_data, NULL, NOT_OK);

    array->data = new_data;
    array->length += extra_items;

    return OK;
}

int ArrayExpandLeftCHARPTR(ArrayCHARPTR* array, size_t extra_items)
{
    char** new_data;

    new_data = realloc(array->data, array->length + extra_items);
    CHECK_RETURN(new_data, NULL, NOT_OK);

    memmove(new_data + extra_items, new_data, extra_items * sizeof(char*));
    array->data = new_data;
    array->length += extra_items;

    return OK;
}

void ArrayMapCHARPTR(const ArrayCHARPTR* array, size_t index, size_t length, void (*f)(char*))
{
    for (size_t k = index; k < length + index; k ++)
        f(array->data[k]);
}

void ArrayApplyCHARPTR(ArrayCHARPTR* array, size_t index, size_t length, void (*f)(char**))
{
    for (size_t k = index; k < length + index; k ++)
        f(&array->data[k]);
}

char* ArrayFoldCHARPTR(const ArrayCHARPTR* array, size_t index, size_t length, 
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