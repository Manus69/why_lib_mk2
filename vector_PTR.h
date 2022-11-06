#ifndef VECTOR_PTR_H
#define VECTOR_PTR_H

#include "array_PTR_interface.h"

#include <stdlib.h>

struct Vector_PTR
{
    Array_PTR*    array;
    size_t      index;
    size_t      length;
};

#endif