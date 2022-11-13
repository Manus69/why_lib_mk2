#ifndef ARRAY_PTR_INTERFACE_H
#define ARRAY_PTR_INTERFACE_H

#include "template_interface.h"
#include "typedefs.h"

#include <stdlib.h>

typedef struct Array_PTR Array_PTR;

Array_PTR* ArrayCreate_PTR(size_t length);
Array_PTR* ArrayCreateZero_PTR(size_t length);
void ArrayDestroy_PTR(Array_PTR* array);
void ArrayDestroyData_PTR(Array_PTR* array);
void ArrayDestroyAll_PTR(Array_PTR* array, void (*f)(void*));
void ArrayDestroyElements_PTR(Array_PTR* array, void (*f)(void*));
size_t ArrayLength_PTR(const Array_PTR* array);
void* ArrayGet_PTR(const Array_PTR* array, size_t index);
void ArraySet_PTR(Array_PTR* array, size_t index, void* value);
int ArrayExpandRight_PTR(Array_PTR* array, size_t extra_items);
int ArrayExpandLeft_PTR(Array_PTR* array, size_t extra_items);
void ArrayMap_PTR(const Array_PTR* array, size_t index, size_t length, void (*f)(void*));
void ArrayApply_PTR(Array_PTR* array, size_t index, size_t length, void (*f)(void**));
void* ArrayFold_PTR(const Array_PTR* array, size_t index, size_t length, 
                void* (*f)(void*, void*), void* initial_value);
void ArraySortSlice_PTR(Array_PTR* array, size_t index, 
                size_t length, int (*cmp)(const void*, const void*));
void ArraySort_PTR(Array_PTR* array, int (*cmp)(const void*, const void*));
size_t ArrayFindIndex_PTR(const Array_PTR* array, void* value,
                size_t index, size_t length, int (*cmp)(const void*, const void*));

#endif