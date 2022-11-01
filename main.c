#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "why.h"

struct test
{
    char* str;
};

#define SIZE 100000000

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
    Vector* vector;

    vector = VectorCreate(int);

    for (int n = 0; n < SIZE; n ++)
    {
        VectorPushBack(vector, int, n);
        // _print_int(VectorGetLength(vector));
    }

    _print_int(VectorGet(vector, int, SIZE - 1));
    
    // VectorApply(vector, int, _print_int);
    VectorDestroy(vector);
}