#include "array_VSTR.h"
#include "array_VSTR_interface.h"
#include "sort_merge_VSTR.h"
#include "macros.h"

#include <stdlib.h>
#include <string.h>

Array_VSTR* ArrayCreate_VSTR(size_t length)
{
    Array_VSTR* array;

    array = malloc(sizeof(*array));
    CHECK_RETURN(array, NULL, NULL);

    array->data = malloc(sizeof(char*) * length);
    if (array->data == NULL)
        RETURN_AFTER(free(array), NULL);
    
    array->length = length;
    
    return array;
}

Array_VSTR* ArrayCreateZero_VSTR(size_t length)
{
    Array_VSTR* array;

    array = ArrayCreate_VSTR(length);
    CHECK_RETURN(array, NULL, NULL);

    memset(array->data, 0, array->length * sizeof(Vector_STR*));

    return array;
}

void ArrayDestroy_VSTR(Array_VSTR* array)
{
    free(array);
}

void ArrayDestroyData_VSTR(Array_VSTR* array)
{
    free(array->data);
}

void ArrayDestroyElements_VSTR(Array_VSTR* array, void (*f)(Vector_STR*))
{
    ArrayMap_VSTR(array, 0, array->length, f);
}

void ArrayDestroyAll_VSTR(Array_VSTR* array, void (*f)(Vector_STR*))
{
    if (f) ArrayDestroyElements_VSTR(array, f);
    ArrayDestroyData_VSTR(array);
    ArrayDestroy_VSTR(array);
}

size_t ArrayLength_VSTR(const Array_VSTR* array)
{
    return array->length;
}

Vector_STR* ArrayGet_VSTR(const Array_VSTR* array, size_t index)
{
    return array->data[index];
}

void ArraySet_VSTR(Array_VSTR* array, size_t index, Vector_STR* value)
{
    array->data[index] = value;
}

int ArrayExpandRight_VSTR(Array_VSTR* array, size_t extra_items)
{
    Vector_STR** new_data;

    new_data = realloc(array->data, (array->length + extra_items) * sizeof(Vector_STR*));
    CHECK_RETURN(new_data, NULL, NOT_OK);

    array->data = new_data;
    array->length += extra_items;

    return OK;
}

int ArrayExpandLeft_VSTR(Array_VSTR* array, size_t extra_items)
{
    Vector_STR** new_data;

    new_data = realloc(array->data, array->length + extra_items);
    CHECK_RETURN(new_data, NULL, NOT_OK);

    memmove(new_data + extra_items, new_data, extra_items * sizeof(Vector_STR*));
    array->data = new_data;
    array->length += extra_items;

    return OK;
}

void ArrayMap_VSTR(const Array_VSTR* array, size_t index, size_t length, void (*f)(Vector_STR*))
{
    CHECK_RETURN(array, NULL, (void)0);
    
    for (size_t k = index; k < length + index; k ++)
        f(array->data[k]);
}

void ArrayApply_VSTR(Array_VSTR* array, size_t index, size_t length, void (*f)(Vector_STR**))
{
    for (size_t k = index; k < length + index; k ++)
        f(&array->data[k]);
}

Vector_STR* ArrayFold_VSTR(const Array_VSTR* array, size_t index, size_t length, 
                Vector_STR* (*f)(Vector_STR*, Vector_STR*), Vector_STR* initial_value)
{
    Vector_STR* result;

    result = initial_value;
    for (size_t k = index; k < length + index; k ++)
    {
        result = f(result, array->data[k]);
    }

    return result;
}

void ArraySortSlice_VSTR(Array_VSTR* array, size_t index, 
                size_t length, int (*cmp)(const Vector_STR*, const Vector_STR*))
{
    return MergeSort_VSTR(array->data, index, length, cmp);
}

void ArraySort_VSTR(Array_VSTR* array, int (*cmp)(const Vector_STR*, const Vector_STR*))
{
    return MergeSort_VSTR(array->data, 0, array->length, cmp);
}

size_t ArrayFindIndex_VSTR(const Array_VSTR* array, const Vector_STR* value,
                size_t index, size_t length, int (*cmp)(const Vector_STR*, const Vector_STR*))
{
    while (index < length)
    {
        CHECK_RETURN(cmp(array->data[index], value), 0, index);
        index ++;
    }

    return -1;
}

Vector_STR** ArrayFind_VSTR(const Array_VSTR* array, const Vector_STR* value,
                size_t index, size_t length, int (*cmp)(const Vector_STR*, const Vector_STR*))
{
    size_t _index;

    _index = ArrayFindIndex_VSTR(array, value, index, length, cmp);
    CHECK_RETURN(_index, (size_t)-1, NULL);

    return &array->data[_index];
}