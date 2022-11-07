#ifndef SORT_MERGE_INT_INTERFACE_H
#define SORT_MERGE_INT_INTERFACE_H

#include "why.h"

#include <stdlib.h>

void MergeSort_INT(int* data, size_t index, size_t length,
                int (*cmp)(const int, const int));

#endif