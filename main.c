#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "why.h"

struct test
{
    char* str;
};

#define SIZE (1 << 27)

void _print_int(int n)
{
    printf("%d\n", n);
}

void _print_str(const char* str)
{
    if (str)
        printf("%s\n", str);
}

int add(int a, int b)
{
    return a + b;
}

void vector_test()
{
    Vector* v = VectorCreate(int);

    for (int n = 1; n < SIZE; n ++)
        VectorPushBack(v, int, n);

    // _print_int(VectorGet(v, int, 1));
    _print_int(VectorFront(v, int));
    _print_int(VectorBack(v, int));

    VectorDestroy(v);
}

int main()
{
    vector_test();

    // char* str = StrConcat("ass", "cock", NULL);

    // _print_str(str);
    // free(str);
}