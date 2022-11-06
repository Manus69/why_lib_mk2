#ifndef ARRAY_T_INTERFACE_H
#define ARRAY_T_INTERFACE_H

#include "why.h"

#include <stdlib.h>

typedef struct Array_T Array_T;

Array_T* ArrayCreateTAG(size_t length);
void ArrayDestroyTAG(Array_T* array);
void ArrayDestroyDataTAG(Array_T* array);
void ArrayDestroyAllTAG(Array_T* array, void (*f)(TYPE));
void ArrayDestroyElementsTAG(Array_T* array, void (*f)(TYPE));
size_t ArrayLengthTAG(const Array_T* array);
TYPE ArrayGetTAG(const Array_T* array, size_t index);
void ArraySetTAG(Array_T* array, size_t index, TYPE value);
int ArrayExpandRightTAG(Array_T* array, size_t extra_items);
int ArrayExpandLeftTAG(Array_T* array, size_t extra_items);
void ArrayMapTAG(const Array_T* array, size_t index, size_t length, void (*f)(TYPE));
void ArrayApplyTAG(Array_T* array, size_t index, size_t length, void (*f)(TYPE*));
TYPE ArrayFoldTAG(const Array_T* array, size_t index, size_t length, 
                TYPE (*f)(TYPE, TYPE), TYPE initial_value);
void ArraySortSliceTAG(Array_T* array, size_t index, 
                size_t length, int (*cmp)(const TYPE, const TYPE));
void ArraySortTAG(Array_T* array, int (*cmp)(const TYPE, const TYPE));

#endif