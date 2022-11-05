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

void MergeSortCHARPTR(char** data, size_t index, size_t length, int (*cmp)(const char*, const char*));
void MergeSortINT(int* data, size_t index, size_t length, int (*cmp)(int, int));

//variadic free
int main()
{
    GenerateTemplate("arrayTYPE.c", "TYPE", "char*", "TAG", "CHARPTR");
}