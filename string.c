#include "string_interface.h"

#include "macro.h"
#include "vector_interface.h"

#include <string.h>
#include <stdarg.h>

size_t  StrLength(const char* str)
{
    return strlen(str);
}

char*   StrCopy(const char* str)
{
    return strdup(str);
}

char*   StrEmpty(size_t length)
{
    char* str;

    str = malloc(length + 1);
    CHECK_RETURN(str, NULL, NULL);
    str[length] = 0;

    return str;
}

#include <stdio.h>
static Vector* _get_lengths(va_list args)
{
    Vector* vector;
    char*   current;
    size_t  current_length;
    size_t  total_length;

    vector = VectorCreate(size_t);
    total_length = 0;

    while ((current = va_arg(args, char *)))
    {
        if ((current_length = strlen(current)))
        {
            VectorPushBack(vector, size_t, current_length);
            printf("%zu\n", VectorBack(vector, size_t));
        }

        total_length += current_length;
    }

    VectorPushBack(vector, size_t, total_length);

    return vector;
}

static char* _combine(va_list args, const Vector* lengths, const char* str)
{
    char*   new_string;
    char*   current;
    size_t  index;
    size_t  length;
    size_t  total_length;

    total_length = VectorBack(lengths, size_t);
    new_string = StrEmpty(total_length);
    CHECK_RETURN(new_string, NULL, NULL);

    memcpy(new_string, str, total_length);
    index = 0;
    while ((current = va_arg(args, char *)))
    {
        length = VectorGet(lengths, size_t, index);
        memcpy(new_string, current, length);
        new_string += length;
    }

    return new_string - total_length;
}

char*   StrConcat(const char* str, ...)
{
    Vector* lengths;
    size_t  length;
    char*   result;
    va_list args, args_copy;

    CHECK_RETURN(str, NULL, NULL);

    va_start(args, str);
    va_copy(args_copy, args);

    lengths = _get_lengths(args_copy);
    CHECK_RETURN(lengths, NULL, NULL);
    length = strlen(str);
    VectorPushFront(lengths, size_t, length);
    VectorSet(lengths, size_t, VectorGetLength(lengths), VectorBack(lengths, size_t) + length);
    result = _combine(args, lengths, str);

    VectorDestroy(lengths);
    va_end(args);
    va_end(args_copy);

    return result;
}