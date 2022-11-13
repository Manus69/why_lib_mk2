#ifndef SORT_MERGE_PTR_INTERFACE_H
#define SORT_MERGE_PTR_INTERFACE_H

#include "template_interface.h"
#include "typedefs.h"

#include <stdlib.h>

void MergeSort_PTR(void** data, size_t index, size_t length,
                int (*cmp)(const void*, const void*));

#endif