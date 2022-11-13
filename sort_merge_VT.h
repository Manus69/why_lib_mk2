#ifndef SORT_MERGE_VT_INTERFACE_H
#define SORT_MERGE_VT_INTERFACE_H

#include "template_interface.h"
#include "typedefs.h"

#include <stdlib.h>

void MergeSort_VT(Vector_T** data, size_t index, size_t length,
                int (*cmp)(const Vector_T*, const Vector_T*));

#endif