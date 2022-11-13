#ifndef SORT_MERGE_VX_INTERFACE_H
#define SORT_MERGE_VX_INTERFACE_H

#include "template_interface.h"
#include "typedefs.h"

#include <stdlib.h>

void MergeSort_VX(Vector_X** data, size_t index, size_t length,
                int (*cmp)(const Vector_X*, const Vector_X*));

#endif