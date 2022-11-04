#ifndef VECTOR_H
#define VECTOR_H

#include "array.h"

typedef struct Vector Vector;

#define V_CAPACITY_DEFAULT (1 << 10)

struct Vector
{
    Array* array;
    size_t left_index;
    size_t length;
};

Vector*     VectorCreate(size_t element_size);
void        VectorDestroy(Vector* vector);
size_t      VectorRightCapacity(const Vector* vector);
int         VectorExpandRight(Vector* vector, size_t n_elements);
size_t      VectorLength(const Vector* vector);
void*       VectorGetPtr(const Vector* vector, size_t index);

#define GetVectorDefinitions(type, name) \
GetArrayDefinitions(type, name) \
type VectorGet##name(const Vector* vector, size_t index) \
{ \
    return ArrayGet##name(vector->array, index + vector->left_index); \
} \
 \
void VectorSet##name(Vector* vector, size_t index, type value) \
{ \
    ArraySet##name(vector->array, index + vector->left_index, value); \
} \
 \
Vector* VectorCreate##name() \
{ \
    return VectorCreate(sizeof(type)); \
}\
\
void VectorPushBack##name(Vector* vector, type value) \
{ \
    if (VectorRightCapacity(vector) || \
    (VectorExpandRight(vector, vector->length * 2) == OK)) \
    { \
        ArraySet##name(vector->array, vector->left_index + vector->length, value); \
        vector->length ++; \
    } \
} \
type VectorBack##name(const Vector* vector) \
{ \
    return ArrayGet##name(vector->array, vector->left_index + vector->length - 1); \
}

#endif