#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "why.h"

struct test
{
    char* str;
};

#define SIZE 3

void _print_int(int n)
{
    printf("%d\n", n);
}

void _print_str(const char* str)
{
    if (str)
        printf("%s\n", str);
}

int main()
{
    Array* array_int;

    array_int = ArrayCreate(int, SIZE);
    
    for (int n = 0; n < SIZE; n ++)
        ArraySet(array_int, int, n, n * n);
    
    // _print_int(ArrayGet(array_int, int, 1));
    // _print_int(ArrayGetLength(array_int));
    ArrayApply(array_int, int, _print_int);

    ArrayDestroy(array_int);
    array_int = ArrayCreate(char *, SIZE);
    ArraySet(array_int, char *, 0, strdup("cock"));
    ArraySet(array_int, char *, 1, strdup("ass"));
    ArraySet(array_int, char *, 2, strdup("gachi muchi"));

    ArrayApply(array_int, char *, _print_str);
    ArraySwap(array_int, char *, 0, 2);
    ArrayApply(array_int, char *, _print_str);
    ArrayDestroyElements(array_int, char *, free);
    ArrayDestroy(array_int);
}