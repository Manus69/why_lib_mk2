#ifndef TABLE_STR_STR_H
#define TABLE_STR_STR_H

#include "vector_STR_interface.h"
#include "array_PTR_interface.h"
#include "template_interface.h"

struct TableEntry_STR_STR
{
    char*        key;
    Vector_STR*   value_vector;
};

struct Table_STR_STR
{
    Array_PTR*  array;
    size_t      (*hash)(const char* item);
    int         (*cmp)(const char*, const char*);
};

#endif