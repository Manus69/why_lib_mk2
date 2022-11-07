#ifndef SORT_MERGE_STR_INTERFACE_H
#define SORT_MERGE_STR_INTERFACE_H

#include "why.h"

#include <stdlib.h>

void MergeSort_STR(char** data, size_t index, size_t length,
                int (*cmp)(const char*, const char*));

#endif