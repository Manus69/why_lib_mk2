#ifndef SORT_MERGE_T_INTERFACE_H
#define SORT_MERGE_T_INTERFACE_H

#include "template_interface.h"

#include <stdlib.h>

void MergeSort_T(TYPE* data, size_t index, size_t length,
                int (*cmp)(const TYPE, const TYPE));

#endif