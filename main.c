#include "string_functions.h"
#include "input_interface.h"
#include "output_interface.h"
#include "template_interface.h"
#include "pair_STR_STR_interface.h"
#include "pair_STR_STR.h"

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

int main()
{
    // GenerateStructures("STR", "char*");
    // GenerateStructures("PTR", "void*");

    GeneratePair("STR", "char*", "ARRAY_STR", "Array_STR");
    // char* a[] = {"ass", "dick"};
    // printf("%s %s\n", a[0], a[1]);
}
