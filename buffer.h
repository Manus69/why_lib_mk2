#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>

struct Buffer
{
    char*   data;
    size_t  index;
    size_t  capacity;
};

#endif