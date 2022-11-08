#ifndef ARRAY_VX_INTERFACE_H
#define ARRAY_VX_INTERFACE_H

#include "template_interface.h"

#include <stdlib.h>

typedef struct Array_VX Array_VX;

Array_VX* ArrayCreate_VX(size_t length);
Array_VX* ArrayCreateZero_VX(size_t length);
void ArrayDestroy_VX(Array_VX* array);
void ArrayDestroyData_VX(Array_VX* array);
void ArrayDestroyAll_VX(Array_VX* array, void (*f)(Vector_X*));
void ArrayDestroyElements_VX(Array_VX* array, void (*f)(Vector_X*));
size_t ArrayLength_VX(const Array_VX* array);
Vector_X* ArrayGet_VX(const Array_VX* array, size_t index);
void ArraySet_VX(Array_VX* array, size_t index, Vector_X* value);
int ArrayExpandRight_VX(Array_VX* array, size_t extra_items);
int ArrayExpandLeft_VX(Array_VX* array, size_t extra_items);
void ArrayMap_VX(const Array_VX* array, size_t index, size_t length, void (*f)(Vector_X*));
void ArrayApply_VX(Array_VX* array, size_t index, size_t length, void (*f)(Vector_X**));
Vector_X* ArrayFold_VX(const Array_VX* array, size_t index, size_t length, 
                Vector_X* (*f)(Vector_X*, Vector_X*), Vector_X* initial_value);
void ArraySortSlice_VX(Array_VX* array, size_t index, 
                size_t length, int (*cmp)(const Vector_X*, const Vector_X*));
void ArraySort_VX(Array_VX* array, int (*cmp)(const Vector_X*, const Vector_X*));
size_t ArrayFindIndex_VX(const Array_VX* array, Vector_X* value,
                size_t index, size_t length, int (*cmp)(const Vector_X*, const Vector_X*));

#endif