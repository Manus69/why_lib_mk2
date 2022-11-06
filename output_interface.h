#ifndef OUTPUT_INTERFACE_H
#define OUTPUT_INTERFACE_H

#include <stdbool.h>

ssize_t WriteToFile(int file, const char* string);
ssize_t WriteToFileName(const char* name, const char* string, bool truncate);

#endif