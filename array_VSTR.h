#ifndef ARRAY_VSTR_H
#define ARRAY_VSTR_H

#include "template_interface.h"
#include "typedefs.h"

#include <stdlib.h>

struct Array_VSTR
{
    Vector_STR**   data;
    size_t  length;
};

#endif