#ifndef ARRAY_TYPE_H
#define ARRAY_TYPE_H

#include "why.h"

#include <stdlib.h>

struct ArrayTAG
{
    TYPE*   data;
    size_t  length;
};

#endif