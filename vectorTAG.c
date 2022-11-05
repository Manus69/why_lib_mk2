#include "vectorTAG.h"
#include "vectorTAG_interface.h"
#include "macros.h"
#include "why.h"

#define DEFAULT_CAPACITY (1 << 2)

VectorTAG* VectorCreateLengthTAG(size_t length)
{
    VectorTAG* vector;

    vector = malloc(sizeof(*vector));
    CHECK_RETURN(vector, NULL, NULL);

    vector->array = ArrayCreateTAG(length);
    if (vector->array == NULL)
        RETURN_AFTER(free(vector), NULL);
    
    vector->index = 0;

    return vector;
}

VectorTAG* VectorCreateTAG()
{
    return VectorCreateLengthTAG(DEFAULT_CAPACITY);
}

void VectorDestroyTAG(VectorTAG* vector)
{
    free(vector);
}

void VectorDestroyAllTAG(VectorTAG* vector)
{
    ArrayDestroyAllTAG(vector->array);
    free(vector);
}

static size_t _map_index(const VectorTAG* vector, size_t index)
{
    return index + vector->index;
}

TYPE VectorGetTAG(const VectorTAG* vector, size_t index)
{
    index = _map_index(vector, index);

    return ArrayGetTAG(vector->array, index);
}

void VectorSetTAG(const VectorTAG* vector, size_t index, TYPE value)
{
    index = _map_index(vector, index);

    return ArraySetTAG(vector->array, index, value);
}

size_t VectorRightCapacity(const VectorTAG* vector)
{
    
}

int VectorExpandBackTAG(VectorTAG* vector, size_t n_items)
{
    return ArrayExpandRightTAG(vector->array, n_items);
}

int VectorPushBackTAG(VectorTAG* vector, TYPE value)
{

}