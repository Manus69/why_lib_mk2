#ifndef TEMPLATE_INTERFACE_H
#define TEMPLATE_INTERFACE_H

#include <stdlib.h>

typedef int TYPE;
typedef int XYPE;

void GenerateTemplate(const char* file_name, size_t n_types, 
                    const char* old_tags[], const char* new_tags[],
                    const char* old_types[], const char* new_types[]);
void GenerateSort(const char* tag, const char* type);
void GenerateArray(const char* tag, const char* type);
void GenerateVector(const char* tag, const char* type);
void GenerateStructures(const char* tag, const char* type);
void GeneratePair(const char* lhs_tag, const char* lhs_type,
                    const char* rhs_tag, const char* rhs_type);
void RegisterTypedef(const char* type, const char* def);

#endif