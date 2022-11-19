#include "array_VT.h"
#include "array_VT_interface.h"
#include "sort_merge_VT.h"
#include "macros.h"

#include <stdlib.h>
#include <string.h>

Array_VT* ArrayCreate_VT(size_t length)
{
    Array_VT* array;

    array = malloc(sizeof(*array));
    CHECK_RETURN(array, NULL, NULL);

    array->data = malloc(sizeof(char*) * length);
    if (array->data == NULL)
        RETURN_AFTER(free(array), NULL);
    
    array->length = length;
    
    return array;
}

Array_VT* ArrayCreateZero_VT(size_t length)
{
    Array_VT* array;

    array = ArrayCreate_VT(length);
    CHECK_RETURN(array, NULL, NULL);

    memset(array->data, 0, array->length * sizeof(Vector_T*));

    return array;
}

void ArrayDestroy_VT(Array_VT* array)
{
    free(array);
}

void ArrayDestroyData_VT(Array_VT* array)
{
    free(array->data);
}

void ArrayDestroyElements_VT(Array_VT* array, void (*f)(Vector_T*))
{
    ArrayMap_VT(array, 0, array->length, f);
}

void ArrayDestroyAll_VT(Array_VT* array, void (*f)(Vector_T*))
{
    if (f) ArrayDestroyElements_VT(array, f);
    ArrayDestroyData_VT(array);
    ArrayDestroy_VT(array);
}

size_t ArrayLength_VT(const Array_VT* array)
{
    return array->length;
}

Vector_T* ArrayGet_VT(const Array_VT* array, size_t index)
{
    return array->data[index];
}

void ArraySet_VT(Array_VT* array, size_t index, Vector_T* value)
{
    array->data[index] = value;
}

int ArrayExpandRight_VT(Array_VT* array, size_t extra_items)
{
    Vector_T** new_data;

    new_data = realloc(array->data, (array->length + extra_items) * sizeof(Vector_T*));
    CHECK_RETURN(new_data, NULL, NOT_OK);

    array->data = new_data;
    array->length += extra_items;

    return OK;
}

int ArrayExpandLeft_VT(Array_VT* array, size_t extra_items)
{
    Vector_T** new_data;

    new_data = realloc(array->data, array->length + extra_items);
    CHECK_RETURN(new_data, NULL, NOT_OK);

    memmove(new_data + extra_items, new_data, extra_items * sizeof(Vector_T*));
    array->data = new_data;
    array->length += extra_items;

    return OK;
}

void ArrayMap_VT(const Array_VT* array, size_t index, size_t length, void (*f)(Vector_T*))
{
    CHECK_RETURN(array, NULL, (void)0);
    
    for (size_t k = index; k < length + index; k ++)
        f(array->data[k]);
}

void ArrayApply_VT(Array_VT* array, size_t index, size_t length, void (*f)(Vector_T**))
{
    CHECK_RETURN(array, NULL, (void)0);
    
    for (size_t k = index; k < length + index; k ++)
        f(&array->data[k]);
}

Vector_T* ArrayFold_VT(const Array_VT* array, size_t index, size_t length, 
                Vector_T* (*f)(Vector_T*, Vector_T*), Vector_T* initial_value)
{
    Vector_T* result;

    result = initial_value;
    for (size_t k = index; k < length + index; k ++)
    {
        result = f(result, array->data[k]);
    }

    return result;
}

void ArraySortSlice_VT(Array_VT* array, size_t index, 
                size_t length, int (*cmp)(const Vector_T*, const Vector_T*))
{
    return MergeSort_VT(array->data, index, length, cmp);
}

void ArraySort_VT(Array_VT* array, int (*cmp)(const Vector_T*, const Vector_T*))
{
    return MergeSort_VT(array->data, 0, array->length, cmp);
}

size_t ArrayFindIndex_VT(const Array_VT* array, const Vector_T* value,
                size_t index, size_t length, int (*cmp)(const Vector_T*, const Vector_T*))
{
    while (index < length)
    {
        CHECK_RETURN(cmp(array->data[index], value), 0, index);
        index ++;
    }

    return -1;
}

Vector_T** ArrayFind_VT(const Array_VT* array, const Vector_T* value,
                size_t index, size_t length, int (*cmp)(const Vector_T*, const Vector_T*))
{
    size_t _index;

    _index = ArrayFindIndex_VT(array, value, index, length, cmp);
    CHECK_RETURN(_index, (size_t)-1, NULL);

    return &array->data[_index];
}