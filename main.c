#include "string_functions.h"
#include "input_interface.h"
#include "output_interface.h"
#include "template_interface.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

//variadic free
int main()
{
    GenerateTemplate("mergeINT.c", NULL, "int", "char*", "INT", "CHARPTR");
}