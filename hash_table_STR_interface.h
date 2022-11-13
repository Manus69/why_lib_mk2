#ifndef HASH_STRABLE_STR_INTERFACE_H
#define HASH_STRABLE_STR_INTERFACE_H

#include "typedefs.h"
#include "template_interface.h"

typedef struct HashTable_STR HashTable_STR;

HashTable_STR* HashTableCreate_STR(size_t size, size_t (*hash)(const char*));
void HashTableDestroyElements_STR(HashTable_STR* table, void (*f)(char*));
void HashTableDestroy_STR(HashTable_STR* table);
void HashTableDestroyAll_STR(HashTable_STR* talbe, void (*f)(char*));
size_t HashTableHash_STR(const HashTable_STR* table, const char* vale);
size_t HashTableInsert_STR(HashTable_STR* table, char* value);
size_t HashTableFindIndex_STR(const HashTable_STR* table, const char* value,
                        int (*cmp)(const char*, const char*));
char** HashTableFind_STR(const HashTable_STR* table, const char* value, 
                        int (*cmp)(const char*, const char*));
void HashTableMap_STR(HashTable_STR* table, void (*f)(char*));

#endif