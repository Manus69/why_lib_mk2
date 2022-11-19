#ifndef VECTOR_X_INTERFACE_H
#define VECTOR_X_INTERFACE_H

#include "array_X_interface.h"
#include "template_interface.h"
#include "typedefs.h"

#include <stdbool.h>

typedef struct Vector_X Vector_X;

Vector_X* VectorCreateLength_X(size_t length);
Vector_X* VectorCreate_X();
void VectorDestroy_X(Vector_X* vector);
void VectorDestroyAll_X(Vector_X* vector, void (*f)(XYPE));
void VectorDestroyElements_X(Vector_X* vector, void (*f)(XYPE));
XYPE VectorGet_X(const Vector_X* vector, size_t index);
void VectorSet_X(Vector_X* vector, size_t index, XYPE value);
XYPE VectorBack_X(const Vector_X* vector);
XYPE VectorPopBack_X(Vector_X* vector);
size_t VectorLength_X(const Vector_X* vector);
size_t VectorRightCapacity_X(const Vector_X* vector);
size_t VectorLeftCapacity_X(const Vector_X* vector);
int VectorExpandRight_X(Vector_X* vector, size_t n_items);
int VectorExpandLeft_X(Vector_X* vector, size_t n_items);
int VectorPushBack_X(Vector_X* vector, XYPE value);
void VectorMap_X(const Vector_X* vector, void (*f)(XYPE));
void VectorApply_X(Vector_X* vector, void (*f)(XYPE*));
XYPE VectorFold_X(const Vector_X* vector, XYPE (*f)(XYPE, XYPE), XYPE initial_value);
void VectorSort_X(Vector_X* vector, int (*cmp)(const XYPE, const XYPE));
size_t VectorFindIndex_X(const Vector_X* vector, const XYPE value, int (*cmp)(const XYPE, const XYPE));
XYPE* VectorFind_X(const Vector_X* vector, const XYPE value, int (*cmp)(const XYPE, const XYPE));
Vector_X* VectorFilter_X(const Vector_X* vector, bool (*predicate)(const XYPE));

#endif