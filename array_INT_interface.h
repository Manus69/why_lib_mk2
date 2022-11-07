#ifndef ARRAY_INT_INTERFACE_H
#define ARRAY_INT_INTERFACE_H

#include "template_interface.h"

#include <stdlib.h>

typedef struct Array_INT Array_INT;

Array_INT* ArrayCreate_INT(size_t length);
Array_INT* ArrayCreateZero_INT(size_t length);
void ArrayDestroy_INT(Array_INT* array);
void ArrayDestroyData_INT(Array_INT* array);
void ArrayDestroyAll_INT(Array_INT* array, void (*f)(int));
void ArrayDestroyElements_INT(Array_INT* array, void (*f)(int));
size_t ArrayLength_INT(const Array_INT* array);
int ArrayGet_INT(const Array_INT* array, size_t index);
void ArraySet_INT(Array_INT* array, size_t index, int value);
int ArrayExpandRight_INT(Array_INT* array, size_t extra_items);
int ArrayExpandLeft_INT(Array_INT* array, size_t extra_items);
void ArrayMap_INT(const Array_INT* array, size_t index, size_t length, void (*f)(int));
void ArrayApply_INT(Array_INT* array, size_t index, size_t length, void (*f)(int*));
int ArrayFold_INT(const Array_INT* array, size_t index, size_t length, 
                int (*f)(int, int), int initial_value);
void ArraySortSlice_INT(Array_INT* array, size_t index, 
                size_t length, int (*cmp)(const int, const int));
void ArraySort_INT(Array_INT* array, int (*cmp)(const int, const int));
size_t ArrayFindIndex_INT(const Array_INT* array, int value,
                size_t index, size_t length, int (*cmp)(const int, const int));

#endif