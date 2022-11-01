#ifndef STRING_INTERFACE_H
#define STRING_INTERFACE_H

#include <stdlib.h>

size_t  StrLength(const char* str);
char*   StrCopy(const char* str);
char*   StrEmpty(size_t length);
char*   StrConcat(const char* str, ...);
//StrRepeat ? 

#endif