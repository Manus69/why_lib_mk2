#include "vector_T.h"
#include "vector_T_interface.h"
#include "macros.h"

#include <stdbool.h>

#define DEFAULT_CAPACITY (1 << 10)

Vector_T* VectorCreateLength_T(size_t length)
{
    Vector_T* vector;

    vector = malloc(sizeof(*vector));
    CHECK_RETURN(vector, NULL, NULL);

    vector->array = ArrayCreate_T(length);
    if (vector->array == NULL)
        RETURN_AFTER(free(vector), NULL);
    
    vector->index = 0;
    vector->length = 0;

    return vector;
}

Vector_T* VectorCreate_T()
{
    return VectorCreateLength_T(DEFAULT_CAPACITY);
}

void VectorDestroy_T(Vector_T* vector)
{
    free(vector);
}

void VectorDestroyAll_T(Vector_T* vector, void (*f)(TYPE))
{
    if (vector)
    {
        if (f) VectorMap_T(vector, f);
        ArrayDestroyAll_T(vector->array, NULL);
        free(vector);
    }
}

void VectorDestroyElements_T(Vector_T* vector, void (*f)(TYPE))
{
    return ArrayDestroyElements_T(vector->array, f);
}

size_t VectorLength_T(const Vector_T* vector)
{
    return vector->length;
}

static size_t _map_index(const Vector_T* vector, size_t index)
{
    return index + vector->index;
}

static size_t _last_item_index(const Vector_T* vector)
{
    return vector->index + vector->length - 1;
}

TYPE VectorGet_T(const Vector_T* vector, size_t index)
{
    index = _map_index(vector, index);

    return ArrayGet_T(vector->array, index);
}

void VectorSet_T(Vector_T* vector, size_t index, TYPE value)
{
    index = _map_index(vector, index);

    return ArraySet_T(vector->array, index, value);
}

size_t VectorRightCapacity_T(const Vector_T* vector)
{
    return ArrayLength_T(vector->array) + vector->index - vector->length;
}

size_t VectorLeftCapacity_T(const Vector_T* vector)
{
    return vector->index;
}

int VectorExpandRight_T(Vector_T* vector, size_t n_items)
{
    n_items = n_items > 0 ? n_items : 1;

    return ArrayExpandRight_T(vector->array, n_items);
}

int VectorExpandLeft_T(Vector_T* vector, size_t n_items)
{
    n_items = n_items > 0 ? n_items : 1;

    if (ArrayExpandLeft_T(vector->array, n_items) != OK)
        return NOT_OK;
    
    vector->index += n_items;

    return OK;
}

int VectorPushBack_T(Vector_T* vector, TYPE value)
{
    if (VectorRightCapacity_T(vector) || 
    (VectorExpandRight_T(vector, 2 * vector->length) == OK))
    {
        ArraySet_T(vector->array, vector->index + vector->length, value);
        vector->length ++;

        return OK;
    }

    return NOT_OK;
}

TYPE VectorPopBack_T(Vector_T* vector)
{
    TYPE value;

    value = ArrayGet_T(vector->array, vector->index + vector->length);
    vector->length --;

    return value;
}

TYPE VectorBack_T(const Vector_T* vector)
{
    return ArrayGet_T(vector->array, _last_item_index(vector));
}

void VectorMap_T(const Vector_T* vector, void (*f)(TYPE))
{
    CHECK_RETURN(vector, NULL, (void)0);
    
    return ArrayMap_T(vector->array, vector->index, vector->length, f);
}

void VectorApply_T(Vector_T* vector, void (*f)(TYPE*))
{
    return ArrayApply_T(vector->array, vector->index, vector->length, f);
}

TYPE VectorFold_T(const Vector_T* vector, TYPE (*f)(TYPE, TYPE), TYPE initial_value)
{
    return ArrayFold_T(vector->array, vector->index, vector->length, f, initial_value);
}

void VectorSort_T(Vector_T* vector, int (*cmp)(const TYPE, const TYPE))
{
    return ArraySortSlice_T(vector->array, vector->index, vector->length, cmp);
}

size_t VectorFindIndex_T(const Vector_T* vector, const TYPE value, int (*cmp)(const TYPE, const TYPE))
{
    return ArrayFindIndex_T(vector->array, value, vector->index, vector->length, cmp)
                     + vector->index;
}

TYPE* VectorFind_T(const Vector_T* vector, const TYPE value, int (*cmp)(const TYPE, const TYPE))
{
    return ArrayFind_T(vector->array, value, vector->index, vector->length, cmp);
}

Vector_T* VectorFilter_T(const Vector_T* vector, bool (*predicate)(const TYPE))
{
    Vector_T* new_vector;
    TYPE value;

    new_vector = VectorCreate_T();
    CHECK_RETURN(new_vector, NULL, NULL);

    for (size_t k = 0; k < vector->length; k ++)
    {
        value = VectorGet_T(vector, k);

        if (predicate(value))
            VectorPushBack_T(new_vector, value);
    }

    return new_vector;
}