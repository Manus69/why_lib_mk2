#include "hash_table_T_interface.h"
#include "hash_table_T.h"
#include "array_VT_interface.h"
#include "vector_T_interface.h"
#include "macros.h"

#define VECTOR_CAPACITY 1 << 2

HashTable_T* HashTableCreate_T(size_t size, size_t (*hash)(const TYPE))
{
    HashTable_T*    table;
    Array_VT*       array;

    array = ArrayCreateZero_VT(size);
    CHECK_RETURN(array, NULL, NULL);

    table = malloc(sizeof(*table));
    if (table == NULL) RETURN_AFTER(free(array), NULL);

    table->array = array;
    table->hash = hash;
    table->n_items = 0;

    return table;
}

void HashTableDestroyElements_T(HashTable_T* table, void (*f)(TYPE))
{
    CHECK_RETURN(table, NULL, (void)0);
    CHECK_RETURN(f, NULL, (void)0);

    for (size_t k = 0; k < ArrayLength_VT(table->array); k ++)
    {
        VectorDestroyElements_T(ArrayGet_VT(table->array, k), f);
    }
}

void HashTableDestroy_T(HashTable_T* table)
{
    CHECK_RETURN(table, NULL, (void)0);

    ArrayDestroyAll_VT(table->array, VectorDestroy_T);
    free(table);
}

void HashTableDestroyAll_T(HashTable_T* table, void (*f)(TYPE))
{
    CHECK_RETURN(table, NULL, (void)0);
    
    HashTableDestroyElements_T(table, f);
    HashTableDestroy_T(table);
}

size_t HashTableHash_T(const HashTable_T* table, const TYPE value)
{
    return table->hash(value) % ArrayLength_VT(table->array);
}

size_t HashTableInsert_T(HashTable_T* table, TYPE value)
{
    size_t      index;
    Vector_T*   vector;

    index = HashTableHash_T(table, value);
    vector = ArrayGet_VT(table->array, index);

    if (vector == NULL)
    {
        vector = VectorCreateLength_T(VECTOR_CAPACITY);
        ArraySet_VT(table->array, index, vector);
    }

    VectorPushBack_T(vector, value);
    table->n_items ++;

    return index;
}

size_t HashTableFindIndex_T(const HashTable_T* table, const TYPE value,
                        int (*cmp)(const TYPE, const TYPE))
{
    Vector_T*   vector;
    size_t      index;
    
    index = HashTableHash_T(table, value);
    vector = ArrayGet_VT(table->array, HashTableHash_T(table, value));
    if (vector == NULL) return -1;

    return VectorFindIndex_T(vector, value, cmp) == (size_t)-1 ? (size_t)-1 : index;
}

TYPE* HashTableFind_T(const HashTable_T* table, const TYPE value, 
                        int (*cmp)(const TYPE, const TYPE))
{
    Vector_T*   vector;
    size_t      index;

    index = HashTableHash_T(table, value);
    vector = ArrayGet_VT(table->array, index);
    if (vector == NULL) return NULL;

    return VectorFind_T(vector, value, cmp);
}

void HashTableMap_T(HashTable_T* table, void (*f)(TYPE))
{
    Vector_T* vector;

    CHECK_RETURN(table, NULL, (void)0);

    for (size_t k = 0; k < ArrayLength_VT(table->array); k ++)
    {
        vector = ArrayGet_VT(table->array, k);
        VectorMap_T(vector, f);
    }
}