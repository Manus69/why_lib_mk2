#include "string_functions.h"
#include "input_interface.h"
#include "output_interface.h"
#include "template_interface.h"

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

void MergeSortCHARPTR(char** data, size_t index, size_t length, int (*cmp)(const char*, const char*));
void MergeSortINT(int* data, size_t index, size_t length, int (*cmp)(int, int));

#include "vectorTAG_interface.h"

//variadic free
int main()
{
    // GenerateTemplate("arrayTAG.c", "TYPE", "char*", "TAG", "CHARPTR");
    // GenerateTemplate("arrayTAG.h", "TYPE", "char*", "TAG", "CHARPTR");
    // GenerateTemplate("arrayTAG_interface.h", "TYPE", "char*", "TAG", "CHARPTR");

    VectorTAG* vector;

    int N = 10;
    vector = VectorCreateTAG();
    for (int n = 0; n < N; n ++)
    {
        VectorPushBackTAG(vector, n);
        // VectorMapTAG(vector, print_int);
        // printf("\n");
    }

    VectorApplyTAG(vector, f);
    int x = VectorFoldTAG(vector, add, 0);
    printf("%d\n", x);
    VectorMapTAG(vector, print_int);
    // print_int(VectorBackTAG(vector));
    VectorDestroyAllTAG(vector);
}