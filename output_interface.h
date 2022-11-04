#ifndef OUTPUT_INTERFACE_H
#define OUTPUT_INTERFACE_H

#include <stdbool.h>

void WriteToFile(int file, const char* string);
void WriteToFileName(const char* name, const char* string, bool truncate);

#endif