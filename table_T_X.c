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

size_t TableFind_T_X(const Table_T_X* table, TYPE key)
{
    size_t      hash;
    Vector_PTR* entries;

    hash = table->hash(key) % TableSize_T_X(table);
    entries = ArrayGet_PTR(table->array, hash);
    CHECK_RETURN(entries, NULL, NOT_FOUND);

    
}