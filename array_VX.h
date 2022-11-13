#ifndef ARRAY_VX_H
#define ARRAY_VX_H

#include "template_interface.h"
#include "typedefs.h"

#include <stdlib.h>

struct Array_VX
{
    Vector_X**   data;
    size_t  length;
};

#endif