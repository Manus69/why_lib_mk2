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
    free(array->data);
    free(array);
}

void*   ArrayGetData(const Array* array)
{
    return array->data;
}

size_t  ArrayGetLength(const Array* array)
{
    return array->length;
}

int     ArrayExpand(const Array* array, size_t extra_length)
{
    void*   data;
    size_t  size;

    CHECK_RETURN(extra_length, 0, OK);

    size = (array->length + extra_length) * array->element_size;
    data = malloc(size);
    CHECK_RETURN(data, NULL, NOT_OK);

    memset(data, 0, size);
    memcpy(data, array->data, array->length * array->element_size);

    return OK;
}
