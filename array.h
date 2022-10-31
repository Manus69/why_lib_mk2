#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

struct Array
{
    void*   data;
    size_t  length;
    size_t  element_size;
};

#endif