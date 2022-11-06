#include "output_interface.h"
#include "macros.h"

#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>

#define PERMS 0666
#define APPEND O_CREAT | O_APPEND | O_RDWR
#define TRUNCATE O_CREAT | O_TRUNC | O_RDWR

ssize_t WriteToFile(int file, const char* string)
{
    return write(file, string, strlen(string));
}

ssize_t WriteToFileName(const char* name, const char* string, bool truncate)
{
    int file;
    int mode;

    mode = truncate ? TRUNCATE : APPEND;

    file = open(name, mode, PERMS);
    if (file > 0)
    {
        return WriteToFile(file, string);
    }
}
