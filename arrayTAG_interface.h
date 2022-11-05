#ifndef ARRAY_TAG_INTERFACE_H
#define ARRAY_TAG_INTERFACE_H

#include "why.h"

#include <stdlib.h>

typedef struct ArrayTAG ArrayTAG;

ArrayTAG* ArrayCreateTAG(size_t length);
void ArrayDestroyTAG(ArrayTAG* array);
void ArrayDestroyDataTAG(ArrayTAG* array);
void ArrayDestroyAllTAG(ArrayTAG* array);
size_t ArrayLengthTAG(const ArrayTAG* array);
TYPE ArrayGetTAG(const ArrayTAG* array, size_t index);
void ArraySetTAG(ArrayTAG* array, size_t index, TYPE value);
int ArrayExpandRightTAG(ArrayTAG* array, size_t extra_items);
int ArrayExpandLeftTAG(ArrayTAG* array, size_t extra_items);
void ArrayApplyTAG(const ArrayTAG* array, size_t index, size_t length, void (*f)(TYPE));

#endif