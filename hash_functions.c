#include "hash_functions.h"

size_t Hash_INT(const int n) //const to match type in prototype
{
    return n;
}

size_t Hash_STR(const char* str)
{
    size_t hash;

    hash = 5381;
    while (*str)
    {
        hash = hash * 33 + *str;
        str ++;
    }

    return hash;
}

size_t HashRolling_STR(const char* str)
{
    size_t p;
    size_t hash;

    p = 31;
    hash = 0;

    while (*str)
    {
        hash = hash * p + *str;
        str ++;
    }

    return hash;
}
