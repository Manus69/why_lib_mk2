#ifndef ARRAY_X_INTERFACE_H
#define ARRAY_X_INTERFACE_H

#include "template_interface.h"
#include "typedefs.h"

#include <stdlib.h>

typedef struct Array_X Array_X;

Array_X* ArrayCreate_X(size_t length);
Array_X* ArrayCreateZero_X(size_t length);
void ArrayDestroy_X(Array_X* array);
void ArrayDestroyData_X(Array_X* array);
void ArrayDestroyAll_X(Array_X* array, void (*f)(XYPE));
void ArrayDestroyElements_X(Array_X* array, void (*f)(XYPE));
size_t ArrayLength_X(const Array_X* array);
XYPE ArrayGet_X(const Array_X* array, size_t index);
void ArraySet_X(Array_X* array, size_t index, XYPE value);
int ArrayExpandRight_X(Array_X* array, size_t extra_items);
int ArrayExpandLeft_X(Array_X* array, size_t extra_items);
void ArrayMap_X(const Array_X* array, size_t index, size_t length, void (*f)(XYPE));
void ArrayApply_X(Array_X* array, size_t index, size_t length, void (*f)(XYPE*));
XYPE ArrayFold_X(const Array_X* array, size_t index, size_t length, 
                XYPE (*f)(XYPE, XYPE), XYPE initial_value);
void ArraySortSlice_X(Array_X* array, size_t index, 
                size_t length, int (*cmp)(const XYPE, const XYPE));
void ArraySort_X(Array_X* array, int (*cmp)(const XYPE, const XYPE));
size_t ArrayFindIndex_X(const Array_X* array, XYPE value,
                size_t index, size_t length, int (*cmp)(const XYPE, const XYPE));

#endif