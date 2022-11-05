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

void printstr(char* str)
{
    printf("\"%s\"\n", str);
}

#include "vectorTAG_interface.h"

//prettyfy
int main()
{
    // GenerateStructuresForType("char*", "CHARPTR");
    // GenerateTemplate("sort_mergeTAG.c", "TYPE", "char*", "TAG", "CHARPTR");
    // GenerateTemplate("sort_mergeTAG_interface.h", "TYPE", "char*", "TAG", "CHARPTR");

    //
    // char* str = ReadFileName("text_file.txt");
    // VectorCHARPTR* vector = StringSplit(str, "\n");
    // VectorMapCHARPTR(vector, printstr);
    // VectorDestroyAllCHARPTR(vector, (void (*)(char*))free);
    // free(str);
}
