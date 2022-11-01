#include "vector.h"
#include "vector_interface.h"
#include "array_interface.h"

size_t _vector_get_index(const Vector* vector)
{
    return vector->index;
}

size_t _vector_map_index(const Vector* vector, size_t index)
{
    return index + vector->index;
}

void    _vector_increment_length(Vector* vector, size_t increment)
{
    vector->length += increment;
}

Vector* _vector_create(size_t capacity, size_t element_size)
{
    Vector* vector;
    Array*  array;

    vector = malloc(sizeof(*vector));
    CHECK_RETURN(vector, NULL, NULL);

    if ((array = ArrayCreateSize(capacity, element_size)))
    {
        vector->array = array;
        vector->index = 0;
        vector->length = 0;

        return vector;
    }

    free(vector);

    return NULL;
}

void    VectorDestroy(Vector* vector)
{
    if (vector)
    {
        ArrayDestroy(vector->array);
        free(vector);
    }
}

Array*  _vector_get_array(const Vector* vector)
{
    return vector->array;
}

size_t  VectorGetLength(const Vector* vector)
{
    return vector->length;
}

size_t  VectorGetRightCapacity(const Vector* vector)
{
    return ArrayGetLength(vector->array) - (vector->index + vector->length);
}

size_t VectorGetLeftCapacity(const Vector* vector)
{
    return vector->index + 1;
}

int VectorExpandRight(Vector* vector, size_t extra_capacity)
{
    extra_capacity = extra_capacity ? extra_capacity : 1;

    return ArrayExpandRight(_vector_get_array(vector), extra_capacity);
}

int VectorExpandLeft(Vector* vector, size_t extra_capacity)
{
    extra_capacity = extra_capacity ? extra_capacity : 1;
    
    if (ArrayExpandLeft(_vector_get_array(vector), extra_capacity) != OK)
        return NOT_OK;
    
    vector->index += extra_capacity;

    return OK;
}