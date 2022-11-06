#include "table_T_X.h"
#include "table_T_X_interface.h"
#include "template_interface.h"
#include "array_PTR_interface.h"
#include "vector_PTR_interface.h"
#include "macros.h"

#include <stdint.h>

#define NOT_FOUND (size_t)-1
#define KEY_VECTOR_SIZE (1 << 1)
#define VALUE_VECTOR_SIZE (1 << 3)
#define TABLE_SIZE (1 << 10)

TableEntry_T_X* TableEntryCreate_T_X(TYPE key)
{
    TableEntry_T_X* entry;

    entry = malloc(sizeof(*entry));
    CHECK_RETURN(entry, NULL, NULL);

    entry->value_vector = VectorCreateLength_X(VALUE_VECTOR_SIZE);
    if (entry->value_vector == NULL) RETURN_AFTER(free(entry), NULL);

    entry->key = key;

    return entry;
}

void TableEntryDestroy_T_X(TableEntry_T_X* entry)
{
    if (entry)
    {
        VectorDestroy_X(entry->value_vector);
        free(entry);
    }
}

void TableEntryDestroyElements_T_X(TableEntry_T_X* entry, void (*f)(XYPE))
{
    if (entry)
    {
        return VectorDestroyElements_X(entry->value_vector, f);
    }
}

void TableEntryMap_T_X(TableEntry_T_X* entry, void (*f)(XYPE))
{
    if (entry)
    {
        return VectorMap_X(entry->value_vector, f);
    }
}

Table_T_X* TableCreate_T_X(size_t size, size_t (*hash)(const TYPE),
                        int (*cmp)(const XYPE, const XYPE))
{
    Table_T_X* table;

    table = malloc(sizeof(*table));
    CHECK_RETURN(table, NULL, NULL);

    table->array = ArrayCreate_PTR(size);
    if (table->array == NULL) RETURN_AFTER(free(table), NULL);

    table->hash = hash;
    table->cmp = cmp;

    return table;
}

size_t TableSize_T_X(const Table_T_X* table)
{
    return ArrayLength_PTR(table->array);
}

void TableDestroy_T_X(Table_T_X* table)
{
    for (size_t k = 0; k < TableSize_T_X(table); k ++)
    {
        VectorMap_PTR(ArrayGet_PTR(table->array, k), 
            (void (*)(void*))TableEntryDestroy_T_X);
    }

    free(table);
}

void TableMap_T_X(Table_T_X* table, void (*f)(XYPE))
{
    Vector_PTR*     entries;
    TableEntry_T_X* entry;

    for (size_t k = 0; k < TableSize_T_X(table); k ++)
    {
        entries = ArrayGet_PTR(table->array, k);
        for (size_t n = 0; n < VectorLength_PTR(entries); n ++)
        {
            entry = VectorGet_PTR(entries, n);
            TableEntryMap_T_X(entry, f);
        }
    }
}

void TableDestroyElements_T_X(Table_T_X* table, void (*f)(XYPE))
{
    return TableMap_T_X(table, f);
}

size_t TableFindIndex_T_X(const Table_T_X* table, TYPE key)
{
    size_t          index;
    size_t          hash;
    Vector_PTR*     entries;
    TableEntry_T_X* entry;

    hash = table->hash(key) % TableSize_T_X(table);
    entries = ArrayGet_PTR(table->array, hash);
    CHECK_RETURN(entries, NULL, NOT_FOUND);

    for (size_t k = 0; k < VectorLength_PTR(entries); k ++)
    {
        entry = VectorGet_PTR(entries, k);
        index = VectorFindIndex_X(entry->value_vector, key, table->cmp);
        CHECK_CONDITION_RETURN(index != NOT_FOUND, hash);
    }

    return NOT_FOUND;
}

int TableInsert_T_X(Table_T_X* table, TYPE key, XYPE value)
{
    
}