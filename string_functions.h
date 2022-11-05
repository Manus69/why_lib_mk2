#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

#include "vectorCHARPTR_interface.h"

char* StringReplace(const char* str, const char* what, const char* value);
VectorCHARPTR* StringSplit(const char* string, const char* separator);
char* StringConcat(const char* str, ...);

#endif