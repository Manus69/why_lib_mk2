#ifndef VECTOR_H
#define VECTOR_H

#include "array_interface.h"

struct Vector
{
    Array* array;
    size_t index;
    size_t length;
};

#endif