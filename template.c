#include "template_interface.h"
#include "string_functions.h"
#include "input_interface.h"
#include "output_interface.h"
#include "macros.h"

#include <stdio.h>

static char* _get_file_name(const char* name, const char* tag, const char* new_tag)
{
    char* new_name;

    new_name = StringReplace(name, tag, new_tag);

    return new_name;
}

static char* _process_file(const char* file_name, const char* base_type,
                    const char* new_type, const char* base_tag, const char* new_tag)
{
    char* content;
    char* type_str;
    char* tag_str;

    if (!file_name) return NULL;
    
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
    if (!content) return ;

    printf("%s\n", content);
    new_name = _get_file_name(name, base_tag, new_tag);
    printf("%s\n", new_name);
    WriteToFileName(new_name, content, true);

    free(content);
    free(new_name);
}

void GenerateTemplate(const char* name,
                    const char* base_type,
                    const char* new_type,
                    const char* base_tag,
                    const char* new_tag)
{
    return _get_file(name, base_type, new_type, base_tag, new_tag);
}