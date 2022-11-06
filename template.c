#include "template_interface.h"
#include "string_functions.h"
#include "input_interface.h"
#include "output_interface.h"
#include "string_functions.h"
#include "memory_interface.h"
#include "macros.h"

#include <stdio.h>

#define TYPE "TYPE"
#define TAG "T"

static char* struct_file_names[] = 
{
    "array_T.c", "array_T.h", "array_T_interface.h",
    "vector_T.c", "vector_T.h", "vector_T_interface.h",
    NULL
};

static char* _get_file_name(const char* name, const char* tag, const char* new_tag)
{
    return StringReplace(name, tag, new_tag);
}

static char* _process_file(const char* file_name, const char* base_type,
                    const char* new_type, const char* base_tag, const char* new_tag)
{
    char* content;
    char* type_str;
    char* tag_str;

    CHECK_RETURN(file_name, NULL, NULL);
    
    content = ReadFileName(file_name);
    CHECK_RETURN(content, NULL, NULL);

    type_str = StringReplace(content, base_type, new_type);
    tag_str = StringReplace(type_str, base_tag, new_tag);

    free(content);
    free(type_str);

    return tag_str;
}

static void _get_file(const char* name, const char* base_type, 
                    const char* new_type, const char* base_tag, const char* new_tag)
{
    char* new_name;
    char* content;

    content = _process_file(name, base_type, new_type, base_tag, new_tag);
    CHECK_RETURN(content, NULL, (void)0);

    // printf("%s\n", content);
    new_name = _get_file_name(name, base_tag, new_tag);
    // printf("%s\n", new_name);
    WriteToFileName(new_name, content, true);
    Free(new_name, content, NULL);
}

void GenerateTemplate(const char* name,
                    const char* base_type,
                    const char* new_type,
                    const char* base_tag,
                    const char* new_tag)
{
    char* _base_tag;
    char* _new_tag;

    _base_tag = StringConcat("_", base_tag, NULL);
    _new_tag = StringConcat("_", new_tag, NULL);

    _get_file(name, base_type, new_type, _base_tag, _new_tag);

    Free(_base_tag, _new_tag, NULL);
}

void GenerateStructuresForType(const char* type, const char* tag)
{
    size_t index;

    index = 0;
    while (struct_file_names[index])
    {
        GenerateTemplate(struct_file_names[index], TYPE, type, TAG, tag);
        index ++;
    }
}