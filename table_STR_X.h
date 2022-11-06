#ifndef TABLE_STR_X_H
#define TABLE_STR_X_H

#include "vector_X_interface.h"
#include "array_PTR_interface.h"
#include "template_interface.h"

struct TableEntry_STR_X
{
    char*        key;
    Vector_X*   value_vector;
};

struct Table_STR_X
{
    Array_PTR*  array;
    size_t      (*hash)(const char* item);
    int         (*cmp)(const char*, const char*);
};

#endif