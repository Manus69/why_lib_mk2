#ifndef HASH_STRABLE_STR_H
#define HASH_STRABLE_STR_H

#include "hash_table_STR_interface.h"
#include "template_interface.h"
#include "typedefs.h"

struct HashTable_STR
{
    Array_VSTR*   array;
    size_t      (*hash)(const char*);
    size_t      n_items;
};

#endif