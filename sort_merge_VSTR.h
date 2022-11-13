#ifndef SORT_MERGE_VSTR_INTERFACE_H
#define SORT_MERGE_VSTR_INTERFACE_H

#include "template_interface.h"
#include "typedefs.h"

#include <stdlib.h>

void MergeSort_VSTR(Vector_STR** data, size_t index, size_t length,
                int (*cmp)(const Vector_STR*, const Vector_STR*));

#endif