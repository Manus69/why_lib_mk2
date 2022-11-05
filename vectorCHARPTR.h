#ifndef VECTOR_CHARPTR_H
#define VECTOR_CHARPTR_H

#include "arrayCHARPTR_interface.h"

#include <stdlib.h>

struct VectorCHARPTR
{
    ArrayCHARPTR*   array;
    size_t      index;
    size_t      length;
};

#endif