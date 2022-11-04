#include "output_interface.h"
#include "macros.h"

#include <unistd.h>
#include <string.h>
#include <fcntl.h>

void WriteToFile(int file, const char* string)
{
    write(file, string, strlen(string));
}

void WriteToFileName(const char* name, const char* string)
{
    int file;

    file = open(name, O_APPEND);
    if (file > 0)
    {
        return WriteToFile(file, string);
    }
}