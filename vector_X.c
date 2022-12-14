#include "vector_X.h"
#include "vector_X_interface.h"
#include "macros.h"

#include <stdbool.h>

#define DEFAULT_CAPACITY (1 << 10)

Vector_X* VectorCreateLength_X(size_t length)
{
    Vector_X* vector;

    vector = malloc(sizeof(*vector));
    CHECK_RETURN(vector, NULL, NULL);

    vector->array = ArrayCreate_X(length);
    if (vector->array == NULL)
        RETURN_AFTER(free(vector), NULL);
    
    vector->index = 0;
    vector->length = 0;

    return vector;
}

Vector_X* VectorCreate_X()
{
    return VectorCreateLength_X(DEFAULT_CAPACITY);
}

void VectorDestroy_X(Vector_X* vector)
{
    CHECK_RETURN(vector, NULL, (void)0);

    ArrayDestroyAll_X(vector->array, NULL);
    free(vector);
}

void VectorDestroyAll_X(Vector_X* vector, void (*f)(XYPE))
{
    CHECK_RETURN(vector, NULL, (void)0);

    if (f) VectorMap_X(vector, f);
    ArrayDestroyAll_X(vector->array, NULL);
    free(vector);
}

void VectorDestroyElements_X(Vector_X* vector, void (*f)(XYPE))
{
    CHECK_RETURN(vector, NULL, (void)0);
    
    return ArrayDestroyElements_X(vector->array, f);
}

size_t VectorLength_X(const Vector_X* vector)
{
    return vector->length;
}

static size_t _map_index(const Vector_X* vector, size_t index)
{
    return index + vector->index;
}

static size_t _last_item_index(const Vector_X* vector)
{
    return vector->index + vector->length - 1;
}

XYPE VectorGet_X(const Vector_X* vector, size_t index)
{
    index = _map_index(vector, index);

    return ArrayGet_X(vector->array, index);
}

void VectorSet_X(Vector_X* vector, size_t index, XYPE value)
{
    index = _map_index(vector, index);

    return ArraySet_X(vector->array, index, value);
}

size_t VectorRightCapacity_X(const Vector_X* vector)
{
    return ArrayLength_X(vector->array) + vector->index - vector->length;
}

size_t VectorLeftCapacity_X(const Vector_X* vector)
{
    return vector->index;
}

int VectorExpandRight_X(Vector_X* vector, size_t n_items)
{
    n_items = n_items > 0 ? n_items : 1;

    return ArrayExpandRight_X(vector->array, n_items);
}

int VectorExpandLeft_X(Vector_X* vector, size_t n_items)
{
    n_items = n_items > 0 ? n_items : 1;

    if (ArrayExpandLeft_X(vector->array, n_items) != OK)
        return NOT_OK;
    
    vector->index += n_items;

    return OK;
}

int VectorPushBack_X(Vector_X* vector, XYPE value)
{
    if (VectorRightCapacity_X(vector) || 
    (VectorExpandRight_X(vector, 2 * vector->length) == OK))
    {
        ArraySet_X(vector->array, vector->index + vector->length, value);
        vector->length ++;

        return OK;
    }

    return NOT_OK;
}

XYPE VectorPopBack_X(Vector_X* vector)
{
    XYPE value;

    value = ArrayGet_X(vector->array, vector->index + vector->length);
    vector->length --;

    return value;
}

XYPE VectorBack_X(const Vector_X* vector)
{
    return ArrayGet_X(vector->array, _last_item_index(vector));
}

void VectorMap_X(const Vector_X* vector, void (*f)(XYPE))
{
    CHECK_RETURN(vector, NULL, (void)0);
    
    return ArrayMap_X(vector->array, vector->index, vector->length, f);
}

void VectorApply_X(Vector_X* vector, void (*f)(XYPE*))
{
    CHECK_RETURN(vector, NULL, (void)0);

    return ArrayApply_X(vector->array, vector->index, vector->length, f);
}

XYPE VectorFold_X(const Vector_X* vector, XYPE (*f)(XYPE, XYPE), XYPE initial_value)
{
    return ArrayFold_X(vector->array, vector->index, vector->length, f, initial_value);
}

void VectorSort_X(Vector_X* vector, int (*cmp)(const XYPE, const XYPE))
{
    return ArraySortSlice_X(vector->array, vector->index, vector->length, cmp);
}

size_t VectorFindIndex_X(const Vector_X* vector, const XYPE value, int (*cmp)(const XYPE, const XYPE))
{
    return ArrayFindIndex_X(vector->array, value, vector->index, vector->length, cmp)
                     + vector->index;
}

XYPE* VectorFind_X(const Vector_X* vector, const XYPE value, int (*cmp)(const XYPE, const XYPE))
{
    return ArrayFind_X(vector->array, value, vector->index, vector->length, cmp);
}

Vector_X* VectorFilter_X(const Vector_X* vector, bool (*predicate)(const XYPE))
{
    Vector_X* new_vector;
    XYPE value;

    new_vector = VectorCreate_X();
    CHECK_RETURN(new_vector, NULL, NULL);

    for (size_t k = 0; k < vector->length; k ++)
    {
        value = VectorGet_X(vector, k);

        if (predicate(value))
            VectorPushBack_X(new_vector, value);
    }

    return new_vector;
}