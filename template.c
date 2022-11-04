#include "template_interface.h"
#include "string_functions.h"
#include "input_interface.h"
#include "output_interface.h"
#include "macros.h"

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

    content = ReadFileName(file_name);
    CHECK_RETURN(content, NULL, NULL);

    type_str = StringReplace(content, base_type, new_type);
    tag_str = StringReplace(type_str, base_tag, new_tag);

    free(content);
    free(type_str);

    return tag_str;
}

void GenerateTemplate(const char* source_name,
                    const char* header_name,
                    const char* base_type,
                    const char* new_type,
                    const char* base_tag,
                    const char* new_tag)
{
    char* header;
    char* source;
    char* new_header_name;
    char* new_source_name;

    header = _process_file(header_name, base_type, new_type, base_tag, new_tag);
    source = _process_file(source_name, base_type, new_type, base_tag, new_tag);

    if (header && source)
    {
        new_header_name = _get_file_name(header_name, base_tag, new_tag);
        new_source_name = _get_file_name(source_name, base_tag, new_tag);

        WriteToFileName(header_name, header, true);
        WriteToFileName(source_name, source, true);

        free(new_header_name);
        free(new_source_name);
    }

    free(header);
    free(source);
}