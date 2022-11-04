#include "vector.h"

Vector* VectorCreate(size_t element_size)
{
    Vector* vector;
    Array*  array;

    array = ArrayCreate(V_CAPACITY_DEFAULT, element_size);
    CHECK_RETURN(array, NULL, NULL);

    if (!(vector = malloc(sizeof(*vector))))
        RETURN_AFTER(ArrayDestroy(array), NULL);

    vector->array = array;
    vector->left_index = 0;
    vector->length = 0;

    return vector;
}

void VectorDestroy(Vector* vector)
{
    if (vector)
    {
        ArrayDestroy(vector->array);
        free(vector);
    }
}

size_t VectorLength(const Vector* vector)
{
    return vector->length;
}
void* VectorGetPtr(const Vector* vector, size_t index)
{
    return ArrayGetPtr(vector->array, index + vector->left_index);
}

size_t VectorRightCapacity(const Vector* vector)
{
    return ArrayLength(vector->array) - (vector->length + vector->left_index);
}

int VectorExpandRight(Vector* vector, size_t n_elements)
{
    n_elements = n_elements == 0 ? 1 : n_elements;

    return ArrayExpandRight(vector->array, n_elements);
}