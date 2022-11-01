#ifndef VECTOR_INTERFACE_H
#define VECTOR_INTERFACE_H

#include "array_interface.h"

#include <stdlib.h>

typedef struct Vector Vector;

#define _V_SIZE_DEFAULT (1 << 10)

Vector* _vector_create(size_t capacity, size_t element_size);
Array*  _vector_get_array(const Vector* vector);
size_t  _vector_get_index(const Vector* vector);
size_t  _vector_map_index(const Vector* vector, size_t index);
void    _vector_increment_length(Vector* vector, size_t increment);

void    VectorDestroy(Vector* vector);
size_t  VectorGetLength(const Vector* vector);
size_t  VectorGetLeftCapacity(const Vector* vector);
size_t  VectorGetRightCapacity(const Vector* vector);
int     VectorExpandRight(Vector* vector, size_t extra_capacity);
int     VectorExpandLeft(Vector* vector, size_t extra_capacity);

#define VectorCreateWithCapacity(type, capacity) _vector_create(capacity, sizeof(type))

#define VectorCreate(type) VectorCreateWithCapacity(type, _V_SIZE_DEFAULT)

#define VectorGet(vector, type, index) \
        ArrayGet(_vector_get_array(vector), type, _vector_map_index(vector, index))

#define VectorSet(vector, type, index, value) \
        ArraySet(_vector_get_array(vector), type, _vector_map_index(vector, index), value)

#define VectorPushBack(vector, type, value) \
        { \
            if (VectorGetRightCapacity(vector) || \
            (VectorExpandRight(vector, 2 * (VectorGetLength(vector)))) == OK) \
            { \
                VectorSet(vector, type, _vector_get_index(vector) + VectorGetLength(vector), value); \
                _vector_increment_length(vector, 1); \
            } \
        } \

#define VectorApply(vector, type, function) \
        ArrayApplySlice(_vector_get_array(vector), type, function, _vector_get_index(vector), VectorGetLength(vector))

#endif