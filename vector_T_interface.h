#ifndef VECTOR_T_INTERFACE_H
#define VECTOR_T_INTERFACE_H

#include "array_T_interface.h"
#include "template_interface.h"
#include "typedefs.h"

#include <stdbool.h>

typedef struct Vector_T Vector_T;

Vector_T* VectorCreateLength_T(size_t length);
Vector_T* VectorCreate_T();
void VectorDestroy_T(Vector_T* vector);
void VectorDestroyAll_T(Vector_T* vector, void (*f)(TYPE));
void VectorDestroyElements_T(Vector_T* vector, void (*f)(TYPE));
TYPE VectorGet_T(const Vector_T* vector, size_t index);
void VectorSet_T(Vector_T* vector, size_t index, TYPE value);
TYPE VectorBack_T(const Vector_T* vector);
TYPE VectorPopBack_T(Vector_T* vector);
size_t VectorLength_T(const Vector_T* vector);
size_t VectorRightCapacity_T(const Vector_T* vector);
size_t VectorLeftCapacity_T(const Vector_T* vector);
int VectorExpandRight_T(Vector_T* vector, size_t n_items);
int VectorExpandLeft_T(Vector_T* vector, size_t n_items);
int VectorPushBack_T(Vector_T* vector, TYPE value);
void VectorMap_T(const Vector_T* vector, void (*f)(TYPE));
void VectorApply_T(Vector_T* vector, void (*f)(TYPE*));
TYPE VectorFold_T(const Vector_T* vector, TYPE (*f)(TYPE, TYPE), TYPE initial_value);
void VectorSort_T(Vector_T* vector, int (*cmp)(const TYPE, const TYPE));
size_t VectorFindIndex_T(const Vector_T* vector, const TYPE value, int (*cmp)(const TYPE, const TYPE));
TYPE* VectorFind_T(const Vector_T* vector, const TYPE value, int (*cmp)(const TYPE, const TYPE));
Vector_T* VectorFilter_T(const Vector_T* vector, bool (*predicate)(const TYPE));

#endif