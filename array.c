#include "array.h"

#include <string.h>

void ArrayInit(Array* array, void* data, size_t length, size_t element_size)
{
    array->data = data;
    array->length = length;
    array->element_size = element_size;
}

Array* ArrayCreate(size_t length, size_t element_size)
{
    Array*  array;
    void*   data;

    array = malloc(sizeof(*array));
    CHECK_RETURN(array, NULL, NULL);

    data = malloc(length * element_size);
    if (!data) RETURN_AFTER(free(array), NULL);
    // memset(data, 0, length * element_size);

    ArrayInit(array, data, length, element_size);

    return array;
}

void ArrayDestroy(Array* array)
{
    if (array)
    {
        free(array->data);
        free(array);
    }
}

size_t ArrayLength(const Array* array)
{
    return array->length;
}

int ArrayExpandRight(Array* array, size_t n_elements)
{
    void* new_data;

    new_data = realloc(array->data, (array->length + n_elements) * array->element_size);
    CHECK_RETURN(new_data, NULL, NOT_OK);

    array->data = new_data;
    array->length += n_elements;

    return OK;
}

void* ArrayGetPtr(const Array* array, size_t index)
{
    return array->data + index * array->element_size;
}

