#include "array.h"
#include "array_interface.h"

#include <string.h>

Array*  ArrayCreateSize(size_t length, size_t element_size)
{
    Array* array;

    CHECK_RETURN(length, 0, NULL);
    array = malloc(sizeof(*array));
    CHECK_RETURN(array, NULL, NULL);

    if ((array->data = malloc(length * element_size)))
    {
        memset(array->data, 0, length * element_size);
        array->length = length;
        array->element_size = element_size;

        return array;
    }

    free(array);

    return NULL;
}

void    ArrayDestroy(Array* array)
{
    if (array)
    {
        free(array->data);
        free(array);
    }
}

void*   ArrayGetData(const Array* array)
{
    return array->data;
}

size_t  ArrayGetLength(const Array* array)
{
    return array->length;
}

// static void _right_memset(void* data, const Array* array, size_t extra_length)
// {
//     memset(data + (array->length * array->element_size), 0, extra_length * array->element_size);
//     memcpy(data, array->data, array->length * array->element_size);
// }

static void _left_memset(void* data, const Array* array, size_t extra_length)
{
    memset(data, 0, extra_length * array->element_size);
    memcpy(data + (extra_length * array->element_size), array->data, array->length * array->element_size);
}

static int _expand(Array* array, size_t extra_length, void (*_memset)(void *, const Array *, size_t))
{
    void*   data;
    size_t  size;

    CHECK_RETURN(extra_length, 0, OK);

    size = (array->length + extra_length) * array->element_size;
    data = malloc(size);
    CHECK_RETURN(data, NULL, NOT_OK);

    _memset(data, array, extra_length);

    free(array->data);
    array->data = data;
    array->length += extra_length;

    return OK;
}

int     ArrayExpandRight(Array* array, size_t extra_length)
{
    void* data;

    data = realloc(array->data,  (array->length + extra_length) * array->element_size);
    CHECK_RETURN(data, NULL, NOT_OK);
    memset(data + array->length * array->element_size, 0, extra_length * array->element_size);

    array->data = data;
    array->length += extra_length;

    return OK;
}

int     ArrayExpandLeft(Array* array, size_t extra_length)
{
    return _expand(array, extra_length, _left_memset);
}
