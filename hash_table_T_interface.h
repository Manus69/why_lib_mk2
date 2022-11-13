#ifndef HASH_TABLE_T_INTERFACE_H
#define HASH_TABLE_T_INTERFACE_H

#include "typedefs.h"
#include "template_interface.h"

typedef struct HashTable_T HashTable_T;

HashTable_T* HashTableCreate_T(size_t size, size_t (*hash)(const TYPE));
void HashTableDestroyElements_T(HashTable_T* table, void (*f)(TYPE));
void HashTableDestroy_T(HashTable_T* table);
void HashTableDestroyAll_T(HashTable_T* talbe, void (*f)(TYPE));
size_t HashTableHash_T(const HashTable_T* table, const TYPE vale);
size_t HashTableInsert_T(HashTable_T* table, TYPE value);
size_t HashTableFindIndex_T(const HashTable_T* table, const TYPE value,
                        int (*cmp)(const TYPE, const TYPE));
TYPE* HashTableFind_T(const HashTable_T* table, const TYPE value, 
                        int (*cmp)(const TYPE, const TYPE));
void HashTableMap_T(HashTable_T* table, void (*f)(TYPE));

#endif