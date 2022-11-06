#ifndef VECTOR_X_H
#define VECTOR_X_H

#include "array_X_interface.h"

#include <stdlib.h>

struct Vector_X
{
    Array_X*    array;
    size_t      index;
    size_t      length;
};

#endif