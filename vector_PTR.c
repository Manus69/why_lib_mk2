#include "vector_PTR.h"
#include "vector_PTR_interface.h"
#include "macros.h"

#include <stdbool.h>

#define DEFAULT_CAPACITY (1 << 10)

Vector_PTR* VectorCreateLength_PTR(size_t length)
{
    Vector_PTR* vector;

    vector = malloc(sizeof(*vector));
    CHECK_RETURN(vector, NULL, NULL);

    vector->array = ArrayCreate_PTR(length);
    if (vector->array == NULL)
        RETURN_AFTER(free(vector), NULL);
    
    vector->index = 0;
    vector->length = 0;

    return vector;
}

Vector_PTR* VectorCreate_PTR()
{
    return VectorCreateLength_PTR(DEFAULT_CAPACITY);
}

void VectorDestroy_PTR(Vector_PTR* vector)
{
    CHECK_RETURN(vector, NULL, (void)0);

    ArrayDestroyAll_PTR(vector->array, NULL);
    free(vector);
}

void VectorDestroyAll_PTR(Vector_PTR* vector, void (*f)(void*))
{
    CHECK_RETURN(vector, NULL, (void)0);

    if (f) VectorMap_PTR(vector, f);
    ArrayDestroyAll_PTR(vector->array, NULL);
    free(vector);
}

void VectorDestroyElements_PTR(Vector_PTR* vector, void (*f)(void*))
{
    CHECK_RETURN(vector, NULL, (void)0);
    
    return ArrayDestroyElements_PTR(vector->array, f);
}

size_t VectorLength_PTR(const Vector_PTR* vector)
{
    return vector->length;
}

static size_t _map_index(const Vector_PTR* vector, size_t index)
{
    return index + vector->index;
}

static size_t _last_item_index(const Vector_PTR* vector)
{
    return vector->index + vector->length - 1;
}

void* VectorGet_PTR(const Vector_PTR* vector, size_t index)
{
    index = _map_index(vector, index);

    return ArrayGet_PTR(vector->array, index);
}

void VectorSet_PTR(Vector_PTR* vector, size_t index, void* value)
{
    index = _map_index(vector, index);

    return ArraySet_PTR(vector->array, index, value);
}

size_t VectorRightCapacity_PTR(const Vector_PTR* vector)
{
    return ArrayLength_PTR(vector->array) + vector->index - vector->length;
}

size_t VectorLeftCapacity_PTR(const Vector_PTR* vector)
{
    return vector->index;
}

int VectorExpandRight_PTR(Vector_PTR* vector, size_t n_items)
{
    n_items = n_items > 0 ? n_items : 1;

    return ArrayExpandRight_PTR(vector->array, n_items);
}

int VectorExpandLeft_PTR(Vector_PTR* vector, size_t n_items)
{
    n_items = n_items > 0 ? n_items : 1;

    if (ArrayExpandLeft_PTR(vector->array, n_items) != OK)
        return NOT_OK;
    
    vector->index += n_items;

    return OK;
}

int VectorPushBack_PTR(Vector_PTR* vector, void* value)
{
    if (VectorRightCapacity_PTR(vector) || 
    (VectorExpandRight_PTR(vector, 2 * vector->length) == OK))
    {
        ArraySet_PTR(vector->array, vector->index + vector->length, value);
        vector->length ++;

        return OK;
    }

    return NOT_OK;
}

void* VectorPopBack_PTR(Vector_PTR* vector)
{
    void* value;

    value = ArrayGet_PTR(vector->array, vector->index + vector->length);
    vector->length --;

    return value;
}

void* VectorBack_PTR(const Vector_PTR* vector)
{
    return ArrayGet_PTR(vector->array, _last_item_index(vector));
}

void VectorMap_PTR(const Vector_PTR* vector, void (*f)(void*))
{
    CHECK_RETURN(vector, NULL, (void)0);
    
    return ArrayMap_PTR(vector->array, vector->index, vector->length, f);
}

void VectorApply_PTR(Vector_PTR* vector, void (*f)(void**))
{
    CHECK_RETURN(vector, NULL, (void)0);

    return ArrayApply_PTR(vector->array, vector->index, vector->length, f);
}

void* VectorFold_PTR(const Vector_PTR* vector, void* (*f)(void*, void*), void* initial_value)
{
    return ArrayFold_PTR(vector->array, vector->index, vector->length, f, initial_value);
}

void VectorSort_PTR(Vector_PTR* vector, int (*cmp)(const void*, const void*))
{
    return ArraySortSlice_PTR(vector->array, vector->index, vector->length, cmp);
}

size_t VectorFindIndex_PTR(const Vector_PTR* vector, const void* value, int (*cmp)(const void*, const void*))
{
    return ArrayFindIndex_PTR(vector->array, value, vector->index, vector->length, cmp)
                     + vector->index;
}

void** VectorFind_PTR(const Vector_PTR* vector, const void* value, int (*cmp)(const void*, const void*))
{
    return ArrayFind_PTR(vector->array, value, vector->index, vector->length, cmp);
}

Vector_PTR* VectorFilter_PTR(const Vector_PTR* vector, bool (*predicate)(const void*))
{
    Vector_PTR* new_vector;
    void* value;

    new_vector = VectorCreate_PTR();
    CHECK_RETURN(new_vector, NULL, NULL);

    for (size_t k = 0; k < vector->length; k ++)
    {
        value = VectorGet_PTR(vector, k);

        if (predicate(value))
            VectorPushBack_PTR(new_vector, value);
    }

    return new_vector;
}