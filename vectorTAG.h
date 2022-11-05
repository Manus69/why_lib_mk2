#ifndef VECTOR_TAG_H
#define VECTOR_TAG_H

#include "arrayTAG_interface.h"

#include <stdlib.h>

struct VectorTAG
{
    ArrayTAG*   array;
    size_t      index;
    size_t      length;
};

#endif