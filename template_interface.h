#ifndef TEMPLATE_INTERFACE_H
#define TEMPLATE_INTERFACE_H

#include <stdlib.h>

typedef int TYPE;
typedef int XYPE;

void GenerateTemplate(const char* file_name, size_t n_types, 
                    const char* old_tags[], const char* new_tags[],
                    const char* old_types[], const char* new_types[]);

#endif