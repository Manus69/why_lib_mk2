#ifndef TEMPLATE_INTERFACE_H
#define TEMPLATE_INTERFACE_H

typedef int TYPE;
typedef int XYPE;

void GenerateTemplate(const char* name,
                    const char* base_type,
                    const char* new_type,
                    const char* base_tag,
                    const char* new_tag);

void GenerateStructuresForType(const char* type, const char* tag);

#endif