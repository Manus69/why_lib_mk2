#ifndef VECTOR_T_INTERFACE_H
#define VECTOR_T_INTERFACE_H

#include "array_T_interface.h"

typedef struct Vector_T Vector_T;

Vector_T* VectorCreateLengthTAG(size_t length);
Vector_T* VectorCreateTAG();
void VectorDestroyTAG(Vector_T* vector);
void VectorDestroyAllTAG(Vector_T* vector, void (*f)(TYPE));
void VectorDestroyElementsTAG(Vector_T* vector, void (*f)(TYPE));
TYPE VectorGetTAG(const Vector_T* vector, size_t index);
void VectorSetTAG(const Vector_T* vector, size_t index, TYPE value);
TYPE VectorBackTAG(const Vector_T* vector);
TYPE VectorPopBackTAG(Vector_T* vector);
size_t VectorRightCapacityTAG(const Vector_T* vector);
size_t VectorLeftCapacityTAG(const Vector_T* vector);
int VectorExpandRightTAG(Vector_T* vector, size_t n_items);
int VectorExpandLeftTAG(Vector_T* vector, size_t n_items);
int VectorPushBackTAG(Vector_T* vector, TYPE value);
void VectorMapTAG(const Vector_T* vector, void (*f)(TYPE));
void VectorApplyTAG(Vector_T* vector, void (*f)(TYPE*));
TYPE VectorFoldTAG(const Vector_T* vector, TYPE (*f)(TYPE, TYPE), TYPE initial_value);
void VectorSortTAG(Vector_T* vector, int (*cmp)(const TYPE, const TYPE));

#endif