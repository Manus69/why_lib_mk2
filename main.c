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


//fake
//prettyfy
//parse int
//list, set, table, 
//unique, filter
//rational, natural, matrix ?
int main()
{
    GenerateStructuresForType("char*", "CHARPTR");
    // GenerateTemplate("sort_mergeTAG.c", "TYPE", "char*", "TAG", "CHARPTR");
    // GenerateTemplate("sort_mergeTAG_interface.h", "TYPE", "char*", "TAG", "CHARPTR");

    //
    // char* str = ReadFileName("text_file.txt");
    // VectorCHARPTR* vector = StringSplit(str, "\n");
    // VectorSortCHARPTR(vector, strcmp);
    // VectorMapCHARPTR(vector, printstr);
    // // printf("%s\n", VectorBackCHARPTR(vector));
    // VectorDestroyAllCHARPTR(vector, (void (*)(char*))free);
    // free(str);

}
