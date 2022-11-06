#ifndef ARRAY_CHARPTR_INTERFACE_H
#define ARRAY_CHARPTR_INTERFACE_H

#include "why.h"

#include <stdlib.h>

typedef struct ArrayCHARPTR ArrayCHARPTR;

ArrayCHARPTR* ArrayCreateCHARPTR(size_t length);
void ArrayDestroyCHARPTR(ArrayCHARPTR* array);
void ArrayDestroyDataCHARPTR(ArrayCHARPTR* array);
void ArrayDestroyAllCHARPTR(ArrayCHARPTR* array, void (*f)(char*));
void ArrayDestroyElementsCHARPTR(ArrayCHARPTR* array, void (*f)(char*));
size_t ArrayLengthCHARPTR(const ArrayCHARPTR* array);
char* ArrayGetCHARPTR(const ArrayCHARPTR* array, size_t index);
void ArraySetCHARPTR(ArrayCHARPTR* array, size_t index, char* value);
int ArrayExpandRightCHARPTR(ArrayCHARPTR* array, size_t extra_items);
int ArrayExpandLeftCHARPTR(ArrayCHARPTR* array, size_t extra_items);
void ArrayMapCHARPTR(const ArrayCHARPTR* array, size_t index, size_t length, void (*f)(char*));
void ArrayApplyCHARPTR(ArrayCHARPTR* array, size_t index, size_t length, void (*f)(char**));
char* ArrayFoldCHARPTR(const ArrayCHARPTR* array, size_t index, size_t length, 
                char* (*f)(char*, char*), char* initial_value);
void ArraySortSliceCHARPTR(ArrayCHARPTR* array, size_t index, 
                size_t length, int (*cmp)(const char*, const char*));
void ArraySortCHARPTR(ArrayCHARPTR* array, int (*cmp)(const char*, const char*));

#endif