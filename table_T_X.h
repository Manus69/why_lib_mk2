#ifndef TABLE_T_X_H
#define TABLE_T_X_H

#include "template_interface.h"
#include "typedefs.h"
#include "hash_table_T_interface.h"


struct Table_T_X
{
    HashTable_T*    key_table;
    Array_X*        value_array;
    size_t          (*hash)(const TYPE);
    int             (*cmp)(const TYPE, const TYPE);
};

#endif