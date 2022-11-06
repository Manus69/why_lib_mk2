#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

#include "template_interface.h"

#include <stdlib.h>

size_t Hash_INT(const int n); //const to match type in prototype
size_t Hash_STR(const char* str);
size_t HashRolling_STR(const char* str);

#endif