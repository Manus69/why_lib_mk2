#include "hash_table_STR_interface.h"
#include "hash_table_STR.h"
#include "array_VSTR_interface.h"
#include "vector_STR_interface.h"
#include "macros.h"

#define VECTOR_CAPACITY 1 << 2

HashTable_STR* HashTableCreate_STR(size_t size, size_t (*hash)(const char*))
{
    HashTable_STR*    table;
    Array_VSTR*       array;

    array = ArrayCreateZero_VSTR(size);
    CHECK_RETURN(array, NULL, NULL);

    table = malloc(sizeof(*table));
    if (table == NULL) RETURN_AFTER(free(array), NULL);

    table->array = array;
    table->hash = hash;
    table->n_items = 0;

    return table;
}

void HashTableDestroyElements_STR(HashTable_STR* table, void (*f)(char*))
{
    CHECK_RETURN(table, NULL, (void)0);
    CHECK_RETURN(f, NULL, (void)0);

    for (size_t k = 0; k < ArrayLength_VSTR(table->array); k ++)
    {
        VectorDestroyElements_STR(ArrayGet_VSTR(table->array, k), f);
    }
}

void HashTableDestroy_STR(HashTable_STR* table)
{
    CHECK_RETURN(table, NULL, (void)0);

    ArrayDestroyAll_VSTR(table->array, VectorDestroy_STR);
    free(table);
}

void HashTableDestroyAll_STR(HashTable_STR* table, void (*f)(char*))
{
    CHECK_RETURN(table, NULL, (void)0);
    
    HashTableDestroyElements_STR(table, f);
    HashTableDestroy_STR(table);
}

size_t HashTableHash_STR(const HashTable_STR* table, const char* value)
{
    return table->hash(value) % ArrayLength_VSTR(table->array);
}

size_t HashTableInsert_STR(HashTable_STR* table, char* value)
{
    size_t      index;
    Vector_STR*   vector;

    index = HashTableHash_STR(table, value);
    vector = ArrayGet_VSTR(table->array, index);

    if (vector == NULL)
    {
        vector = VectorCreateLength_STR(VECTOR_CAPACITY);
        ArraySet_VSTR(table->array, index, vector);
    }

    VectorPushBack_STR(vector, value);
    table->n_items ++;

    return index;
}

size_t HashTableFindIndex_STR(const HashTable_STR* table, const char* value,
                        int (*cmp)(const char*, const char*))
{
    Vector_STR*   vector;
    size_t      index;
    
    index = HashTableHash_STR(table, value);
    vector = ArrayGet_VSTR(table->array, HashTableHash_STR(table, value));
    if (vector == NULL) return -1;

    return VectorFindIndex_STR(vector, value, cmp) == (size_t)-1 ? (size_t)-1 : index;
}

char** HashTableFind_STR(const HashTable_STR* table, const char* value, 
                        int (*cmp)(const char*, const char*))
{
    Vector_STR*   vector;
    size_t      index;

    index = HashTableHash_STR(table, value);
    vector = ArrayGet_VSTR(table->array, index);
    if (vector == NULL) return NULL;

    return VectorFind_STR(vector, value, cmp);
}

void HashTableMap_STR(HashTable_STR* table, void (*f)(char*))
{
    Vector_STR* vector;

    CHECK_RETURN(table, NULL, (void)0);

    for (size_t k = 0; k < ArrayLength_VSTR(table->array); k ++)
    {
        vector = ArrayGet_VSTR(table->array, k);
        VectorMap_STR(vector, f);
    }
}