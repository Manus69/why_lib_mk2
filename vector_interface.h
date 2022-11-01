#ifndef VECTOR_INTERFACE_H
#define VECTOR_INTERFACE_H

#include "array_interface.h"
#include "vector.h"

#include <stdlib.h>

typedef struct Vector Vector;

#define _V_SIZE_DEFAULT (1 << 10)

Vector* _vector_create(size_t capacity, size_t element_size);

void    VectorDestroy(Vector* vector);
size_t  VectorGetLength(const Vector* vector);
size_t  VectorGetLeftCapacity(const Vector* vector);
size_t  VectorGetRightCapacity(const Vector* vector);
int     VectorExpandRight(Vector* vector, size_t extra_capacity);
int     VectorExpandLeft(Vector* vector, size_t extra_capacity);

#define VectorCreateWithCapacity(_type, _capacity) _vector_create(_capacity, sizeof(_type))

#define VectorCreate(_type) VectorCreateWithCapacity(_type, _V_SIZE_DEFAULT)

#define VectorGet(_vector, _type, _index) \
        ArrayGet(_vector->array, _type, ((_vector->index) + _index))

#define VectorSet(_vector, _type, _index, _value) \
        ArraySet(_vector->array, _type, _vector->index + _index, _value)

#define VectorPushBack(_vector, _type, _value) \
{ \
    if (VectorGetRightCapacity(_vector) || \
    (VectorExpandRight(_vector, 2 * (_vector->length))) == OK) \
    { \
        VectorSet(_vector, _type, _vector->index + _vector->length, _value); \
        _vector->length ++; \
    } \
}

#define VectorPushFront(_vector, _type, _value) \
{ \
    if (VectorGetLeftCapacity(_vector) || \
    (VectorExpandLeft(_vector, 2 * (VectorGetLeftCapacity(_vector)))) == OK) \
    { \
        ArraySet(_vector->array, _type, _vector->index, _value); \
        _vector->index --; \
        _vector->length ++; \
    } \
}

#define VectorApply(_vector, _type, _function) \
        ArrayApplySlice(_vector->array, _type, _function, _vector->index, _vector->length)

#define VectorFront(_vector, _type) VectorGet(_vector, _type, 0)

#define VectorBack(_vector, _type) VectorGet(_vector, _type, _vector->length - 1)

#endif