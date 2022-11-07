#include "template_interface.h"
#include "string_functions.h"
#include "input_interface.h"
#include "output_interface.h"
#include "string_functions.h"
#include "memory_functions.h"
#include "pair_STR_STR_interface.h"
#include "macros.h"

#include <stdio.h>
#include <string.h>

#define TYPE "TYPE"
#define TAG "T"

// static char* struct_file_names[] = 
// {
//     "array_T.c", "array_T.h", "array_T_interface.h",
//     "vector_T.c", "vector_T.h", "vector_T_interface.h",
//     "sort_merge_T.c", "sort_merge_T_interface.h",
//     NULL
// };

// static char* _get_file_name(const char* name, const char* tag, const char* new_tag)
// {
//     return StringReplace(name, tag, new_tag);
// }

// static char* _process_file(const char* file_name, const char* base_type,
//                     const char* new_type, const char* base_tag, const char* new_tag)
// {
//     char* content;
//     char* type_str;
//     char* tag_str;

//     CHECK_RETURN(file_name, NULL, NULL);
    
//     content = ReadFileName(file_name);
//     CHECK_RETURN(content, NULL, NULL);

//     type_str = StringReplace(content, base_type, new_type);
//     tag_str = StringReplace(type_str, base_tag, new_tag);

//     free(content);
//     free(type_str);

//     return tag_str;
// }

// static void _get_file(const char* name, const char* base_type, 
//                     const char* new_type, const char* base_tag, const char* new_tag)
// {
//     char* new_name;
//     char* content;

//     content = _process_file(name, base_type, new_type, base_tag, new_tag);
//     CHECK_RETURN(content, NULL, (void)0);

//     // printf("%s\n", content);
//     new_name = _get_file_name(name, base_tag, new_tag);
//     // printf("%s\n", new_name);
//     WriteToFileName(new_name, content, true);
//     Free(new_name, content, NULL);
// }

// void GenerateTemplate(const char* name,
//                     const char* base_type,
//                     const char* new_type,
//                     const char* base_tag,
//                     const char* new_tag)
// {
//     char* _base_tag;
//     char* _new_tag;

//     _base_tag = StringConcat("_", base_tag, NULL);
//     _new_tag = StringConcat("_", new_tag, NULL);

//     _get_file(name, base_type, new_type, _base_tag, _new_tag);

//     Free(_base_tag, _new_tag, NULL);
// }

// void GenerateStructuresForType(const char* type, const char* tag)
// {
//     size_t index;

//     index = 0;
//     while (struct_file_names[index])
//     {
//         GenerateTemplate(struct_file_names[index], TYPE, type, TAG, tag);
//         index ++;
//     }
// }

static char** _process_tags(size_t n_tags, const char* tags[])
{
    char** new_tags;

    new_tags = malloc(sizeof(char*) * n_tags);
    CHECK_RETURN(new_tags, NULL, NULL);

    for (size_t k = 0; k < n_tags; k ++)
    {
        new_tags[k] = StringConcat("_", tags[k], NULL);
    }

    return new_tags;
}

static char* _get_file_name(const char* file_name, size_t n_tags,
                    const char* old_tags[], const char* new_tags[])
{
    char* name;
    char* new_name;

    CHECK_RETURN(n_tags, 0, NULL);

    name = strdup(file_name);
    for (size_t k = 0; k < n_tags; k ++)
    {
        new_name = StringReplace(name, old_tags[k], new_tags[k]);
        free(name);
        name = new_name;
    }

    return new_name;
}

static char* _replace(const char* content, size_t n_types,
                    const char* old_tags[], const char* new_tags[],
                    const char* old_types[], const char* new_types[])
{
    char* current;
    char* store;
    char** old_tag_strings;
    char** new_tag_strings;

    CHECK_RETURN(n_types, 0, NULL);

    old_tag_strings = _process_tags(n_types, old_tags);
    new_tag_strings = _process_tags(n_types, new_tags);

    current = strdup(content);
    for (size_t k = 0; k < n_types; k ++)
    {
        store = StringReplace(current, old_tag_strings[k], new_tag_strings[k]);
        free(current);
        current = StringReplace(store, old_types[k], new_types[k]);
    }

    return current;
}

void GenerateTemplate(const char* file_name, size_t n_types, 
                    const char* old_tags[], const char* new_tags[],
                    const char* old_types[], const char* new_types[])
{
    char* new_name;
    char* new_content;
    char* content;

    content = ReadFileName(file_name);
    CHECK_RETURN(content, NULL, (void)0);

    new_content = _replace(content, n_types, old_tags, new_tags, old_types, new_types);
    if (new_content == NULL) RETURN_AFTER(free(content), (void)0);

    // printf("%s\n", new_content);

    new_name = _get_file_name(file_name, n_types, old_tags, new_tags);
    if (new_name == NULL) RETURN_AFTER(Free(content, new_content, NULL), (void)0);

    // printf("%s\n", new_name);
    WriteToFileName(new_name, new_content, true);

    Free(content, new_content, new_name, NULL);
}