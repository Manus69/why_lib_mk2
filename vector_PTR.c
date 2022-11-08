#include "vector_PTR.h"
#include "vector_PTR_interface.h"
#include "macros.h"
#include "why.h"

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
    free(vector);
}

void VectorDestroyAll_PTR(Vector_PTR* vector, void (*f)(void*))
{
    if (vector)
    {
        if (f) VectorMap_PTR(vector, f);
        ArrayDestroyAll_PTR(vector->array, NULL);
        free(vector);
    }
}

void VectorDestroyElements_PTR(Vector_PTR* vector, void (*f)(void*))
{
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
    return ArrayMap_PTR(vector->array, vector->index, vector->length, f);
}

void VectorApply_PTR(Vector_PTR* vector, void (*f)(void**))
{
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

size_t VectorFindIndex_PTR(const Vector_PTR* vector, void* value, int (*cmp)(const void*, const void*))
{
    return ArrayFindIndex_PTR(vector->array, value, vector->index, vector->length, cmp)
                     + vector->index;
}