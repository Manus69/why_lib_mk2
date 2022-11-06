#ifndef VECTOR_STR_H
#define VECTOR_STR_H

#include "array_STR_interface.h"

#include <stdlib.h>

struct Vector_STR
{
    Array_STR*    array;
    size_t      index;
    size_t      length;
};

#endif