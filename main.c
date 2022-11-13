#include "string_functions.h"
#include "input_interface.h"
#include "output_interface.h"
#include "template_interface.h"
#include "pair_STR_STR_interface.h"
#include "pair_STR_STR.h"
#include "hash_table_STR_interface.h"
#include "hash_functions.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

int cmp(const char* lhs, const char* rhs)
{
    return strcmp(lhs, rhs);
}

int cmpINT(int lhs, int rhs)
{
    return lhs - rhs;
}

void print_int(int n)
{
    printf("%d ", n);
}

void f(int* n)
{
    *n += 1;
}

int add(int a, int b)
{
    return a + b;
}

void printstr(char* str)
{
    printf("\"%s\"\n", str);
}

//fake
//prettyfy
//parse int
//list, set, table, avl
//unique, filter
//rational, natural
//generic print
//variadic destructors
//format

#include "array_VX_interface.h"
#include "vector_X_interface.h"

void _destroy(Vector_X* v)
{
    VectorDestroyAll_X(v, NULL);
}

int main()
{
    // GenerateStructures("STR", "char*");
    // GenerateStructures("PTR", "void*");
    // GenerateStructures("X", "XYPE");
    // GenerateArray("VT", "Vector_T*");

    // GenerateHashTable("STR", "char*");

    char* str = ReadFileName("text_file.txt");
    Vector_STR* vector = StringSplit(str, "\n");

    VectorSort_STR(vector, strcmp);
    // VectorMap_STR(vector, printstr);

    HashTable_STR* table = HashTableCreate_STR(1000, HashRolling_STR);
    for (size_t k = 0; k < VectorLength_STR(vector); k ++)
    {
        HashTableInsert_STR(table, VectorGet_STR(vector, k));
    }

    // HashTableMap_STR(table, printstr);

    free(str);
    VectorDestroyAll_STR(vector, (void (*)(char*))free);

    // HashTableDestroy_STR(table);
}
