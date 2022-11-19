#ifndef ARRAY_VT_INTERFACE_H
#define ARRAY_VT_INTERFACE_H

#include "template_interface.h"
#include "typedefs.h"

#include <stdlib.h>

typedef struct Array_VT Array_VT;

Array_VT* ArrayCreate_VT(size_t length);
Array_VT* ArrayCreateZero_VT(size_t length);
void ArrayDestroy_VT(Array_VT* array);
void ArrayDestroyData_VT(Array_VT* array);
void ArrayDestroyAll_VT(Array_VT* array, void (*f)(Vector_T*));
void ArrayDestroyElements_VT(Array_VT* array, void (*f)(Vector_T*));
size_t ArrayLength_VT(const Array_VT* array);
Vector_T* ArrayGet_VT(const Array_VT* array, size_t index);
void ArraySet_VT(Array_VT* array, size_t index, Vector_T* value);
int ArrayExpandRight_VT(Array_VT* array, size_t extra_items);
int ArrayExpandLeft_VT(Array_VT* array, size_t extra_items);
void ArrayMap_VT(const Array_VT* array, size_t index, size_t length, void (*f)(Vector_T*));
void ArrayApply_VT(Array_VT* array, size_t index, size_t length, void (*f)(Vector_T**));
Vector_T* ArrayFold_VT(const Array_VT* array, size_t index, size_t length, 
                Vector_T* (*f)(Vector_T*, Vector_T*), Vector_T* initial_value);
void ArraySortSlice_VT(Array_VT* array, size_t index, 
                size_t length, int (*cmp)(const Vector_T*, const Vector_T*));
void ArraySort_VT(Array_VT* array, int (*cmp)(const Vector_T*, const Vector_T*));
size_t ArrayFindIndex_VT(const Array_VT* array, const Vector_T* value,
                size_t index, size_t length, int (*cmp)(const Vector_T*, const Vector_T*));
Vector_T** ArrayFind_VT(const Array_VT* array, const Vector_T* value,
                size_t index, size_t length, int (*cmp)(const Vector_T*, const Vector_T*));

#endif