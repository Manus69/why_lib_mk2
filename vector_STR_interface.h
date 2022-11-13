#ifndef VECTOR_STR_INTERFACE_H
#define VECTOR_STR_INTERFACE_H

#include "array_STR_interface.h"
#include "template_interface.h"
#include "typedefs.h"

#include <stdbool.h>

typedef struct Vector_STR Vector_STR;

Vector_STR* VectorCreateLength_STR(size_t length);
Vector_STR* VectorCreate_STR();
void VectorDestroy_STR(Vector_STR* vector);
void VectorDestroyAll_STR(Vector_STR* vector, void (*f)(char*));
void VectorDestroyElements_STR(Vector_STR* vector, void (*f)(char*));
char* VectorGet_STR(const Vector_STR* vector, size_t index);
void VectorSet_STR(Vector_STR* vector, size_t index, char* value);
char* VectorBack_STR(const Vector_STR* vector);
char* VectorPopBack_STR(Vector_STR* vector);
size_t VectorLength_STR(const Vector_STR* vector);
size_t VectorRightCapacity_STR(const Vector_STR* vector);
size_t VectorLeftCapacity_STR(const Vector_STR* vector);
int VectorExpandRight_STR(Vector_STR* vector, size_t n_items);
int VectorExpandLeft_STR(Vector_STR* vector, size_t n_items);
int VectorPushBack_STR(Vector_STR* vector, char* value);
void VectorMap_STR(const Vector_STR* vector, void (*f)(char*));
void VectorApply_STR(Vector_STR* vector, void (*f)(char**));
char* VectorFold_STR(const Vector_STR* vector, char* (*f)(char*, char*), char* initial_value);
void VectorSort_STR(Vector_STR* vector, int (*cmp)(const char*, const char*));
size_t VectorFindIndex_STR(const Vector_STR* vector, char* value, int (*cmp)(const char*, const char*));
Vector_STR* VectorFilter_STR(const Vector_STR* vector, bool (*predicate)(const char*));
char** VectorFind_STR(const Vector_STR* vector, char* value, int (*cmp)(const char*, const char*));

#endif