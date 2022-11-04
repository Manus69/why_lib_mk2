#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#include "string_functions.h"
#include "input_interface.h"

int main()
{
    char* str = ReadFileName("buffer_interface.h");
    printf("%s\n", str);
    char* new = StringReplace(str, "Buffer", "COCK SUCKER");
    printf("%s\n", new);

    free(str);
    free(new);
}