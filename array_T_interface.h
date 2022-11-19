#ifndef ARRAY_T_INTERFACE_H
#define ARRAY_T_INTERFACE_H

#include "template_interface.h"
#include "typedefs.h"

#include <stdlib.h>

typedef struct Array_T Array_T;

Array_T* ArrayCreate_T(size_t length);
Array_T* ArrayCreateZero_T(size_t length);
void ArrayDestroy_T(Array_T* array);
void ArrayDestroyData_T(Array_T* array);
void ArrayDestroyAll_T(Array_T* array, void (*f)(TYPE));
void ArrayDestroyElements_T(Array_T* array, void (*f)(TYPE));
size_t ArrayLength_T(const Array_T* array);
TYPE ArrayGet_T(const Array_T* array, size_t index);
void ArraySet_T(Array_T* array, size_t index, TYPE value);
int ArrayExpandRight_T(Array_T* array, size_t extra_items);
int ArrayExpandLeft_T(Array_T* array, size_t extra_items);
void ArrayMap_T(const Array_T* array, size_t index, size_t length, void (*f)(TYPE));
void ArrayApply_T(Array_T* array, size_t index, size_t length, void (*f)(TYPE*));
TYPE ArrayFold_T(const Array_T* array, size_t index, size_t length, 
                TYPE (*f)(TYPE, TYPE), TYPE initial_value);
void ArraySortSlice_T(Array_T* array, size_t index, 
                size_t length, int (*cmp)(const TYPE, const TYPE));
void ArraySort_T(Array_T* array, int (*cmp)(const TYPE, const TYPE));
size_t ArrayFindIndex_T(const Array_T* array, const TYPE value,
                size_t index, size_t length, int (*cmp)(const TYPE, const TYPE));
TYPE* ArrayFind_T(const Array_T* array, const TYPE value,
                size_t index, size_t length, int (*cmp)(const TYPE, const TYPE));
TYPE* ArrayPoint_T(const Array_T* array, size_t index);

#endif