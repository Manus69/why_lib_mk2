#include "table_T_X_interface.h"
#include "table_T_X.h"
#include "array_T_interface.h"
#include "macros.h"
#include "memory_functions.h"

#define TABLE_CAPACITY (1 << 3)

Table_T_X* TableCreateWithCapacity_T_X(size_t capacity,
                                    size_t (*hash)(const TYPE),
                                    int (*cmp)(const TYPE, const TYPE))
{
    Table_T_X* table;

    table = malloc(sizeof(*table));
    CHECK_RETURN(table, NULL, NULL);

    table->key_table = HashTableCreate_T(capacity, hash);
    table->value_array = ArrayCreateZero_T(capacity);
    table->hash = hash;
    table->cmp = cmp;

    if (table->key_table && table->value_array) return table;

    Free(table->key_table, table->value_array, NULL);

    return NULL;
}

Table_T_X* TableCreate_T_X(size_t (*hash)(const TYPE), int (*cmp)(const TYPE, const TYPE))
{
    return TableCreateWithCapacity_T_X(TABLE_CAPACITY, hash, cmp);
}

void TableMapKeys_T_X(Table_T_X* table, void (*f)(TYPE))
{
    return HashTableMap_T(table->key_table, f);
}

void TableMapValues_T_X(Table_T_X* table, void (*f)(XYPE))
{
    return ArrayMap_T(table->value_array, 0, ArrayLength_T(table->value_array), f);
}

void TableDestroyKeys_T_X(Table_T_X* table, void (*f)(TYPE))
{
    CHECK_RETURN(table, NULL, (void)0);

    return HashTableDestroyElements_T(table->key_table, f);
}

void TableDestoryValues_T_X(Table_T_X* table, void (*f)(XYPE))
{
    CHECK_RETURN(table, NULL, (void)0);

    return ArrayDestroyElements_T(table->value_array, f);
}

void TableDestroy_T_X(Table_T_X* table)
{
    CHECK_RETURN(table, NULL, (void)0);

    HashTableDestroy_T(table->key_table);
    ArrayDestroyData_T(table->value_array);
    ArrayDestroy_T(table->value_array);
}

void TableDestroyAll_T_X(Table_T_X* table, void (*f)(TYPE), void (*g)(XYPE))
{
    CHECK_RETURN(table, NULL, (void)0);

    TableDestroyKeys_T_X(table, f);
    TableDestoryValues_T_X(table, g);
    TableDestroy_T_X(table);
}

static size_t _insert_key(Table_T_X* table, const TYPE key)
{
    return HashTableInsert_T(table->key_table, key);
}

static XYPE* _insert_value(Table_T_X* table, size_t index, const XYPE value)
{
    // XYPE* previous;

}

size_t TableFindIndex_T_X(const Table_T_X* table, const TYPE key)
{
    return HashTableFindIndex_T(table->key_table, key, table->cmp);
}

size_t TableSet_T_X(Table_T_X* table, const TYPE key, const XYPE value)
{
    size_t index;

    index = TableFindIndex_T_X(table, key);
}

XYPE* TableGet_T_X(const Table_T_X* table, const TYPE key)
{

}