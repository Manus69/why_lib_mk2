#include "vector_T.h"
#include "vector_T_interface.h"
#include "macros.h"
#include "why.h"

#define DEFAULT_CAPACITY (1 << 10)

Vector_T* VectorCreateLengthTAG(size_t length)
{
    Vector_T* vector;

    vector = malloc(sizeof(*vector));
    CHECK_RETURN(vector, NULL, NULL);

    vector->array = ArrayCreateTAG(length);
    if (vector->array == NULL)
        RETURN_AFTER(free(vector), NULL);
    
    vector->index = 0;
    vector->length = 0;

    return vector;
}

Vector_T* VectorCreateTAG()
{
    return VectorCreateLengthTAG(DEFAULT_CAPACITY);
}

void VectorDestroyTAG(Vector_T* vector)
{
    free(vector);
}

void VectorDestroyAllTAG(Vector_T* vector, void (*f)(TYPE))
{
    if (f) VectorMapTAG(vector, f);
    ArrayDestroyAllTAG(vector->array, NULL);
    free(vector);
}

void VectorDestroyElementsTAG(Vector_T* vector, void (*f)(TYPE))
{
    ArrayDestroyElementsTAG(vector->array, f);
}

static size_t _map_index(const Vector_T* vector, size_t index)
{
    return index + vector->index;
}

static size_t _last_item_index(const Vector_T* vector)
{
    return vector->index + vector->length - 1;
}

TYPE VectorGetTAG(const Vector_T* vector, size_t index)
{
    index = _map_index(vector, index);

    return ArrayGetTAG(vector->array, index);
}

void VectorSetTAG(const Vector_T* vector, size_t index, TYPE value)
{
    index = _map_index(vector, index);

    return ArraySetTAG(vector->array, index, value);
}

size_t VectorRightCapacityTAG(const Vector_T* vector)
{
    return ArrayLengthTAG(vector->array) + vector->index - vector->length;
}

size_t VectorLeftCapacityTAG(const Vector_T* vector)
{
    return vector->index;
}

int VectorExpandRightTAG(Vector_T* vector, size_t n_items)
{
    n_items = n_items > 0 ? n_items : 1;

    return ArrayExpandRightTAG(vector->array, n_items);
}

int VectorExpandLeftTAG(Vector_T* vector, size_t n_items)
{
    n_items = n_items > 0 ? n_items : 1;

    if (ArrayExpandLeftTAG(vector->array, n_items) != OK)
        return NOT_OK;
    
    vector->index += n_items;

    return OK;
}

int VectorPushBackTAG(Vector_T* vector, TYPE value)
{
    if (VectorRightCapacityTAG(vector) || 
    (VectorExpandRightTAG(vector, 2 * vector->length) == OK))
    {
        ArraySetTAG(vector->array, vector->index + vector->length, value);
        vector->length ++;

        return OK;
    }

    return NOT_OK;
}

TYPE VectorPopBackTAG(Vector_T* vector)
{
    TYPE value;

    value = ArrayGetTAG(vector->array, vector->index + vector->length);
    vector->length --;

    return value;
}

TYPE VectorBackTAG(const Vector_T* vector)
{
    return ArrayGetTAG(vector->array, _last_item_index(vector));
}

void VectorMapTAG(const Vector_T* vector, void (*f)(TYPE))
{
    return ArrayMapTAG(vector->array, vector->index, vector->length, f);
}

void VectorApplyTAG(Vector_T* vector, void (*f)(TYPE*))
{
    return ArrayApplyTAG(vector->array, vector->index, vector->length, f);
}

TYPE VectorFoldTAG(const Vector_T* vector, TYPE (*f)(TYPE, TYPE), TYPE initial_value)
{
    return ArrayFoldTAG(vector->array, vector->index, vector->length, f, initial_value);
}

void VectorSortTAG(Vector_T* vector, int (*cmp)(const TYPE, const TYPE))
{
    return ArraySortSliceTAG(vector->array, vector->index, vector->length, cmp);
}
