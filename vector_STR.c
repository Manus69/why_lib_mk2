#include "vector_STR.h"
#include "vector_STR_interface.h"
#include "macros.h"

#include <stdbool.h>

#define DEFAULT_CAPACITY (1 << 10)

Vector_STR* VectorCreateLength_STR(size_t length)
{
    Vector_STR* vector;

    vector = malloc(sizeof(*vector));
    CHECK_RETURN(vector, NULL, NULL);

    vector->array = ArrayCreate_STR(length);
    if (vector->array == NULL)
        RETURN_AFTER(free(vector), NULL);
    
    vector->index = 0;
    vector->length = 0;

    return vector;
}

Vector_STR* VectorCreate_STR()
{
    return VectorCreateLength_STR(DEFAULT_CAPACITY);
}

void VectorDestroy_STR(Vector_STR* vector)
{
    free(vector);
}

void VectorDestroyAll_STR(Vector_STR* vector, void (*f)(char*))
{
    if (vector)
    {
        if (f) VectorMap_STR(vector, f);
        ArrayDestroyAll_STR(vector->array, NULL);
        free(vector);
    }
}

void VectorDestroyElements_STR(Vector_STR* vector, void (*f)(char*))
{
    return ArrayDestroyElements_STR(vector->array, f);
}

size_t VectorLength_STR(const Vector_STR* vector)
{
    return vector->length;
}

static size_t _map_index(const Vector_STR* vector, size_t index)
{
    return index + vector->index;
}

static size_t _last_item_index(const Vector_STR* vector)
{
    return vector->index + vector->length - 1;
}

char* VectorGet_STR(const Vector_STR* vector, size_t index)
{
    index = _map_index(vector, index);

    return ArrayGet_STR(vector->array, index);
}

void VectorSet_STR(Vector_STR* vector, size_t index, char* value)
{
    index = _map_index(vector, index);

    return ArraySet_STR(vector->array, index, value);
}

size_t VectorRightCapacity_STR(const Vector_STR* vector)
{
    return ArrayLength_STR(vector->array) + vector->index - vector->length;
}

size_t VectorLeftCapacity_STR(const Vector_STR* vector)
{
    return vector->index;
}

int VectorExpandRight_STR(Vector_STR* vector, size_t n_items)
{
    n_items = n_items > 0 ? n_items : 1;

    return ArrayExpandRight_STR(vector->array, n_items);
}

int VectorExpandLeft_STR(Vector_STR* vector, size_t n_items)
{
    n_items = n_items > 0 ? n_items : 1;

    if (ArrayExpandLeft_STR(vector->array, n_items) != OK)
        return NOT_OK;
    
    vector->index += n_items;

    return OK;
}

int VectorPushBack_STR(Vector_STR* vector, char* value)
{
    if (VectorRightCapacity_STR(vector) || 
    (VectorExpandRight_STR(vector, 2 * vector->length) == OK))
    {
        ArraySet_STR(vector->array, vector->index + vector->length, value);
        vector->length ++;

        return OK;
    }

    return NOT_OK;
}

char* VectorPopBack_STR(Vector_STR* vector)
{
    char* value;

    value = ArrayGet_STR(vector->array, vector->index + vector->length);
    vector->length --;

    return value;
}

char* VectorBack_STR(const Vector_STR* vector)
{
    return ArrayGet_STR(vector->array, _last_item_index(vector));
}

void VectorMap_STR(const Vector_STR* vector, void (*f)(char*))
{
    CHECK_RETURN(vector, NULL, (void)0);
    
    return ArrayMap_STR(vector->array, vector->index, vector->length, f);
}

void VectorApply_STR(Vector_STR* vector, void (*f)(char**))
{
    return ArrayApply_STR(vector->array, vector->index, vector->length, f);
}

char* VectorFold_STR(const Vector_STR* vector, char* (*f)(char*, char*), char* initial_value)
{
    return ArrayFold_STR(vector->array, vector->index, vector->length, f, initial_value);
}

void VectorSort_STR(Vector_STR* vector, int (*cmp)(const char*, const char*))
{
    return ArraySortSlice_STR(vector->array, vector->index, vector->length, cmp);
}

size_t VectorFindIndex_STR(const Vector_STR* vector, const char* value, int (*cmp)(const char*, const char*))
{
    return ArrayFindIndex_STR(vector->array, value, vector->index, vector->length, cmp)
                     + vector->index;
}

char** VectorFind_STR(const Vector_STR* vector, const char* value, int (*cmp)(const char*, const char*))
{
    return ArrayFind_STR(vector->array, value, vector->index, vector->length, cmp);
}

Vector_STR* VectorFilter_STR(const Vector_STR* vector, bool (*predicate)(const char*))
{
    Vector_STR* new_vector;
    char* value;

    new_vector = VectorCreate_STR();
    CHECK_RETURN(new_vector, NULL, NULL);

    for (size_t k = 0; k < vector->length; k ++)
    {
        value = VectorGet_STR(vector, k);

        if (predicate(value))
            VectorPushBack_STR(new_vector, value);
    }

    return new_vector;
}