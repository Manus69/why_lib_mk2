#ifndef SORT_MERGE_X_INTERFACE_H
#define SORT_MERGE_X_INTERFACE_H

#include "template_interface.h"

#include <stdlib.h>

void MergeSort_X(XYPE* data, size_t index, size_t length,
                int (*cmp)(const XYPE, const XYPE));

#endif