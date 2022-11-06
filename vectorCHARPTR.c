#include "vectorCHARPTR.h"
#include "vectorCHARPTR_interface.h"
#include "macros.h"
#include "why.h"

#define DEFAULT_CAPACITY (1 << 10)

VectorCHARPTR* VectorCreateLengthCHARPTR(size_t length)
{
    VectorCHARPTR* vector;

    vector = malloc(sizeof(*vector));
    CHECK_RETURN(vector, NULL, NULL);

    vector->array = ArrayCreateCHARPTR(length);
    if (vector->array == NULL)
        RETURN_AFTER(free(vector), NULL);
    
    vector->index = 0;
    vector->length = 0;

    return vector;
}

VectorCHARPTR* VectorCreateCHARPTR()
{
    return VectorCreateLengthCHARPTR(DEFAULT_CAPACITY);
}

void VectorDestroyCHARPTR(VectorCHARPTR* vector)
{
    free(vector);
}

void VectorDestroyAllCHARPTR(VectorCHARPTR* vector, void (*f)(char*))
{
    if (f) VectorMapCHARPTR(vector, f);
    ArrayDestroyAllCHARPTR(vector->array, NULL);
    free(vector);
}

void VectorDestroyElementsCHARPTR(VectorCHARPTR* vector, void (*f)(char*))
{
    ArrayDestroyElementsCHARPTR(vector->array, f);
}

static size_t _map_index(const VectorCHARPTR* vector, size_t index)
{
    return index + vector->index;
}

static size_t _last_item_index(const VectorCHARPTR* vector)
{
    return vector->index + vector->length - 1;
}

char* VectorGetCHARPTR(const VectorCHARPTR* vector, size_t index)
{
    index = _map_index(vector, index);

    return ArrayGetCHARPTR(vector->array, index);
}

void VectorSetCHARPTR(const VectorCHARPTR* vector, size_t index, char* value)
{
    index = _map_index(vector, index);

    return ArraySetCHARPTR(vector->array, index, value);
}

size_t VectorRightCapacityCHARPTR(const VectorCHARPTR* vector)
{
    return ArrayLengthCHARPTR(vector->array) + vector->index - vector->length;
}

size_t VectorLeftCapacityCHARPTR(const VectorCHARPTR* vector)
{
    return vector->index;
}

int VectorExpandRightCHARPTR(VectorCHARPTR* vector, size_t n_items)
{
    n_items = n_items > 0 ? n_items : 1;

    return ArrayExpandRightCHARPTR(vector->array, n_items);
}

int VectorExpandLeftCHARPTR(VectorCHARPTR* vector, size_t n_items)
{
    n_items = n_items > 0 ? n_items : 1;

    if (ArrayExpandLeftCHARPTR(vector->array, n_items) != OK)
        return NOT_OK;
    
    vector->index += n_items;

    return OK;
}

int VectorPushBackCHARPTR(VectorCHARPTR* vector, char* value)
{
    if (VectorRightCapacityCHARPTR(vector) || 
    (VectorExpandRightCHARPTR(vector, 2 * vector->length) == OK))
    {
        ArraySetCHARPTR(vector->array, vector->index + vector->length, value);
        vector->length ++;

        return OK;
    }

    return NOT_OK;
}

char* VectorBackCHARPTR(const VectorCHARPTR* vector)
{
    return ArrayGetCHARPTR(vector->array, _last_item_index(vector));
}

void VectorMapCHARPTR(const VectorCHARPTR* vector, void (*f)(char*))
{
    return ArrayMapCHARPTR(vector->array, vector->index, vector->length, f);
}

void VectorApplyCHARPTR(VectorCHARPTR* vector, void (*f)(char**))
{
    return ArrayApplyCHARPTR(vector->array, vector->index, vector->length, f);
}

char* VectorFoldCHARPTR(const VectorCHARPTR* vector, char* (*f)(char*, char*), char* initial_value)
{
    return ArrayFoldCHARPTR(vector->array, vector->index, vector->length, f, initial_value);
}

void VectorSortCHARPTR(VectorCHARPTR* vector, int (*cmp)(const char*, const char*))
{
    return ArraySortSliceCHARPTR(vector->array, vector->index, vector->length, cmp);
}
