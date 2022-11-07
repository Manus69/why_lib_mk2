#ifndef ARRAY_PTR_H
#define ARRAY_PTR_H

#include "template_interface.h"

#include <stdlib.h>

struct Array_PTR
{
    void**   data;
    size_t  length;
};

#endif