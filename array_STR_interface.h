#ifndef ARRAY_STR_INTERFACE_H
#define ARRAY_STR_INTERFACE_H

#include "template_interface.h"
#include "typedefs.h"

#include <stdlib.h>

typedef struct Array_STR Array_STR;

Array_STR* ArrayCreate_STR(size_t length);
Array_STR* ArrayCreateZero_STR(size_t length);
void ArrayDestroy_STR(Array_STR* array);
void ArrayDestroyData_STR(Array_STR* array);
void ArrayDestroyAll_STR(Array_STR* array, void (*f)(char*));
void ArrayDestroyElements_STR(Array_STR* array, void (*f)(char*));
size_t ArrayLength_STR(const Array_STR* array);
char* ArrayGet_STR(const Array_STR* array, size_t index);
void ArraySet_STR(Array_STR* array, size_t index, char* value);
int ArrayExpandRight_STR(Array_STR* array, size_t extra_items);
int ArrayExpandLeft_STR(Array_STR* array, size_t extra_items);
void ArrayMap_STR(const Array_STR* array, size_t index, size_t length, void (*f)(char*));
void ArrayApply_STR(Array_STR* array, size_t index, size_t length, void (*f)(char**));
char* ArrayFold_STR(const Array_STR* array, size_t index, size_t length, 
                char* (*f)(char*, char*), char* initial_value);
void ArraySortSlice_STR(Array_STR* array, size_t index, 
                size_t length, int (*cmp)(const char*, const char*));
void ArraySort_STR(Array_STR* array, int (*cmp)(const char*, const char*));
size_t ArrayFindIndex_STR(const Array_STR* array, const char* value,
                size_t index, size_t length, int (*cmp)(const char*, const char*));
char** ArrayFind_STR(const Array_STR* array, const char* value,
                size_t index, size_t length, int (*cmp)(const char*, const char*));

#endif