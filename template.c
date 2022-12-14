#include "template_interface.h"
#include "string_functions.h"
#include "input_interface.h"
#include "output_interface.h"
#include "string_functions.h"
#include "memory_functions.h"
#include "pair_STR_STR_interface.h"
#include "macros.h"
#include "debug_functions.h"

#include <stdio.h>
#include <string.h>

#define TYPE "TYPE"
#define TAG "T"
#define XYPE "XYPE"
#define XAG "X"

#define MERGE_SRC "sort_merge_T.c"
#define MERGE_HEADER "sort_merge_T.h"

#define ARRAY_SRC "array_T.c"
#define ARRAY_HEADER "array_T.h"
#define ARRAY_INTERFACE "array_T_interface.h"

#define VECTOR_SRC "vector_T.c"
#define VECTOR_HEADER "vector_T.h"
#define VECTOR_INTERFACE "vector_T_interface.h"

#define HASH_SRC "hash_table_T.c"
#define HASH_HEADER "hash_table_T.h"
#define HASH_INTERFACE "hash_table_T_interface.h"

#define PAIR_SRC "pair_T_X.c"
#define PAIR_HEADER "pair_T_X.h"

#define TYPEDEF_HEADER "typedefs.h"

#define TEMPLATE(file, N, old_tags, new_tags, old_types, new_types)\
GenerateTemplate(file, N,\
                (const char*[])old_tags, (const char*[])new_tags,\
                (const char*[])old_types, (const char*[])new_types)

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
        free(store);
    }

    MapRegion(old_tag_strings, n_types, sizeof(char*), (void (*)(void*))FreePtr);
    MapRegion(new_tag_strings, n_types, sizeof(char*), (void (*)(void*))FreePtr);
    Free(old_tag_strings, new_tag_strings, NULL);

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

    new_name = _get_file_name(file_name, n_types, old_tags, new_tags);
    if (new_name == NULL) RETURN_AFTER(Free(content, new_content, NULL), (void)0);

    WriteToFileName(new_name, new_content, true);

    Free(content, new_content, new_name, NULL);
}

void GenerateSort(const char* tag, const char* type)
{
    TEMPLATE(MERGE_SRC, 1, {TAG}, {tag}, {TYPE}, {type});
    TEMPLATE(MERGE_HEADER, 1, {TAG}, {tag}, {TYPE}, {type});
}

void GenerateArray(const char* tag, const char* type)
{
    char* name;

    GenerateSort(tag, type);

    TEMPLATE(ARRAY_SRC, 1, {TAG}, {tag}, {TYPE}, {type});
    TEMPLATE(ARRAY_HEADER, 1, {TAG}, {tag}, {TYPE}, {type});
    TEMPLATE(ARRAY_INTERFACE, 1, {TAG}, {tag}, {TYPE}, {type});

    name = StringConcat("Array_", tag, NULL);

    RegisterStruct(name);
    free(name);
}

void GenerateVector(const char* tag, const char* type)
{
    char* name;

    GenerateArray(tag, type);

    TEMPLATE(VECTOR_SRC, 1, {TAG}, {tag}, {TYPE}, {type});
    TEMPLATE(VECTOR_HEADER, 1, {TAG}, {tag}, {TYPE}, {type});
    TEMPLATE(VECTOR_INTERFACE, 1, {TAG}, {tag}, {TYPE}, {type});

    name = StringConcat("Vector_", tag, NULL);
    RegisterStruct(name);
    free(name);
}

void GenerateStructures(const char* tag, const char* type)
{
    GenerateVector(tag, type);
}

void GenerateHashTable(const char* tag, const char* type)
{
    char* vector_type;
    char* array_tag;

    vector_type = StringConcat("Vector_", tag, "*", NULL); 
    array_tag = StringConcat("V", tag, NULL);

    GenerateVector(tag, type);
    GenerateArray(array_tag, vector_type);

    GenerateTemplate(HASH_SRC, 2,
                    (const char*[]){TAG, "VT"}, (const char*[]){tag, array_tag},
                    (const char*[]){TYPE, TYPE}, (const char*[]){type, type});

    GenerateTemplate(HASH_HEADER, 2,
                    (const char*[]){TAG, "VT"}, (const char*[]){tag, array_tag},
                    (const char*[]){TYPE, TYPE}, (const char*[]){type, type});
    
    TEMPLATE(HASH_INTERFACE, 1, {TAG}, {tag}, {TYPE}, {type});

    Free(vector_type, array_tag, NULL);
}

void GeneratePair(const char* lhs_tag, const char* lhs_type,
                    const char* rhs_tag, const char* rhs_type)
{
    GenerateTemplate(PAIR_SRC, 2,
                    (const char*[]){TAG, XAG}, (const char*[]){lhs_tag, rhs_tag},
                    (const char*[]){TYPE, XYPE}, (const char*[]){lhs_type, rhs_type});
    
    GenerateTemplate(PAIR_HEADER, 2,
                    (const char*[]){TAG, XAG}, (const char*[]){lhs_tag, rhs_tag},
                    (const char*[]){TYPE, XYPE}, (const char*[]){lhs_type, rhs_type});
}

void RegisterTypedef(const char* type, const char* def)
{
    char* content;
    char* tail;
    char* result;

    content = ReadFileName(TYPEDEF_HEADER);
    CHECK_RETURN(content, NULL, (void)0);

    tail = StringConcat("typedef ", type, " ", def, ";\n\n#endif", NULL);
    result = StringReplace(content, "\n#endif", tail);

    WriteToFileName(TYPEDEF_HEADER, result, true);

    Free(content, tail, result, NULL);
}

void RegisterStruct(const char* name)
{
    char* _struct;

    _struct = StringConcat("struct ", name, NULL);
    RegisterTypedef(_struct, name);
    free(_struct);
}