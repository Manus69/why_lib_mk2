#ifndef VECTOR_PTR_INTERFACE_H
#define VECTOR_PTR_INTERFACE_H

#include "array_PTR_interface.h"
#include "template_interface.h"
#include "typedefs.h"

#include <stdbool.h>

typedef struct Vector_PTR Vector_PTR;

Vector_PTR* VectorCreateLength_PTR(size_t length);
Vector_PTR* VectorCreate_PTR();
void VectorDestroy_PTR(Vector_PTR* vector);
void VectorDestroyAll_PTR(Vector_PTR* vector, void (*f)(void*));
void VectorDestroyElements_PTR(Vector_PTR* vector, void (*f)(void*));
void* VectorGet_PTR(const Vector_PTR* vector, size_t index);
void VectorSet_PTR(Vector_PTR* vector, size_t index, void* value);
void* VectorBack_PTR(const Vector_PTR* vector);
void* VectorPopBack_PTR(Vector_PTR* vector);
size_t VectorLength_PTR(const Vector_PTR* vector);
size_t VectorRightCapacity_PTR(const Vector_PTR* vector);
size_t VectorLeftCapacity_PTR(const Vector_PTR* vector);
int VectorExpandRight_PTR(Vector_PTR* vector, size_t n_items);
int VectorExpandLeft_PTR(Vector_PTR* vector, size_t n_items);
int VectorPushBack_PTR(Vector_PTR* vector, void* value);
void VectorMap_PTR(const Vector_PTR* vector, void (*f)(void*));
void VectorApply_PTR(Vector_PTR* vector, void (*f)(void**));
void* VectorFold_PTR(const Vector_PTR* vector, void* (*f)(void*, void*), void* initial_value);
void VectorSort_PTR(Vector_PTR* vector, int (*cmp)(const void*, const void*));
size_t VectorFindIndex_PTR(const Vector_PTR* vector, const void* value, int (*cmp)(const void*, const void*));
void** VectorFind_PTR(const Vector_PTR* vector, const void* value, int (*cmp)(const void*, const void*));
Vector_PTR* VectorFilter_PTR(const Vector_PTR* vector, bool (*predicate)(const void*));

#endif