#ifndef ARRAY_T_H
#define ARRAY_T_H

#include "template_interface.h"
#include "typedefs.h"

#include <stdlib.h>

struct Array_T
{
    TYPE*   data;
    size_t  length;
};

#endif