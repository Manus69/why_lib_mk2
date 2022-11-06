#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include "vector_STR_interface.h"

char* StringReplace(const char* str, const char* what, const char* value);
char* StringConcat(const char* str, ...);
Vector_STR* StringSplit(const char* string, const char* separator);

#endif