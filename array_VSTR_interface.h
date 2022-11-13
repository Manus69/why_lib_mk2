#ifndef ARRAY_VSTR_INTERFACE_H
#define ARRAY_VSTR_INTERFACE_H

#include "template_interface.h"
#include "typedefs.h"

#include <stdlib.h>

typedef struct Array_VSTR Array_VSTR;

Array_VSTR* ArrayCreate_VSTR(size_t length);
Array_VSTR* ArrayCreateZero_VSTR(size_t length);
void ArrayDestroy_VSTR(Array_VSTR* array);
void ArrayDestroyData_VSTR(Array_VSTR* array);
void ArrayDestroyAll_VSTR(Array_VSTR* array, void (*f)(Vector_STR*));
void ArrayDestroyElements_VSTR(Array_VSTR* array, void (*f)(Vector_STR*));
size_t ArrayLength_VSTR(const Array_VSTR* array);
Vector_STR* ArrayGet_VSTR(const Array_VSTR* array, size_t index);
void ArraySet_VSTR(Array_VSTR* array, size_t index, Vector_STR* value);
int ArrayExpandRight_VSTR(Array_VSTR* array, size_t extra_items);
int ArrayExpandLeft_VSTR(Array_VSTR* array, size_t extra_items);
void ArrayMap_VSTR(const Array_VSTR* array, size_t index, size_t length, void (*f)(Vector_STR*));
void ArrayApply_VSTR(Array_VSTR* array, size_t index, size_t length, void (*f)(Vector_STR**));
Vector_STR* ArrayFold_VSTR(const Array_VSTR* array, size_t index, size_t length, 
                Vector_STR* (*f)(Vector_STR*, Vector_STR*), Vector_STR* initial_value);
void ArraySortSlice_VSTR(Array_VSTR* array, size_t index, 
                size_t length, int (*cmp)(const Vector_STR*, const Vector_STR*));
void ArraySort_VSTR(Array_VSTR* array, int (*cmp)(const Vector_STR*, const Vector_STR*));
size_t ArrayFindIndex_VSTR(const Array_VSTR* array, const Vector_STR* value,
                size_t index, size_t length, int (*cmp)(const Vector_STR*, const Vector_STR*));
Vector_STR** ArrayFind_VSTR(const Array_VSTR* array, const Vector_STR* value,
                size_t index, size_t length, int (*cmp)(const Vector_STR*, const Vector_STR*));

#endif