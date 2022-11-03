#ifndef MACROS_H
#define MACROS_H

#include <stdlib.h>

#define OK 0
#define NOT_OK 1

#define CHECK_RETURN(value, reference, return_value) \
        if (value == reference) return return_value;

#define RETURN_AFTER(action, return_value) \
{ \
    action; \
    return return_value;\
}

#define GET(ptr, type, index) ((type *)ptr)[index]

#define SET(ptr, type, index, value) ((type *)ptr)[index] = value

#define SETPTR(ptr, type, index, value_ptr) ((type *)ptr)[index] = *(type *)value_ptr

#endif