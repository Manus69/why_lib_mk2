#ifndef VECTOR_T_H
#define VECTOR_T_H

#include "array_T_interface.h"
#include "typedefs.h"

#include <stdlib.h>

struct Vector_T
{
    Array_T*    array;
    size_t      index;
    size_t      length;
};

#endif