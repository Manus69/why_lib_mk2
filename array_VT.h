#ifndef ARRAY_VT_H
#define ARRAY_VT_H

#include "template_interface.h"
#include "typedefs.h"

#include <stdlib.h>

struct Array_VT
{
    Vector_T**   data;
    size_t  length;
};

#endif