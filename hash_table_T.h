#ifndef HASH_TABLE_T_H
#define HASH_TABLE_T_H

#include "hash_table_T_interface.h"
#include "template_interface.h"
#include "typedefs.h"

struct HashTable_T
{
    Array_VT*   array;
    size_t      (*hash)(const TYPE);
    size_t      n_items;
};

#endif