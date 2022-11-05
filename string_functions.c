#include "string_functions.h"
#include "buffer_interface.h"
#include "vectorCHARPTR_interface.h"
#include "macros.h"

#include <string.h>

static void _replace(Buffer* buffer, const char* str, const char* what, const char* value)
{
    char* next;

    CHECK_RETURN(*str, 0, (void)0);
    
    next = strstr(str, what);
    
    if (next == NULL)
    {
        return (void)BufferSet(buffer, str);
    }

    BufferSetLength(buffer, str, next - str);
    BufferSet(buffer, value);
    str = next + strlen(what);

    return _replace(buffer, str, what, value);
}

char* StringReplace(const char* str, const char* what, const char* value)
{
    Buffer* buffer;
    char*   result;

    CHECK_RETURN(str, NULL, NULL);
    CHECK_CONDITION_RETURN(!what || !value, strdup(str));
    CHECK_CONDITION_RETURN(*what == 0, NULL);
    
    buffer = BufferCreate(strlen(str));
    CHECK_RETURN(buffer, NULL, NULL);

    _replace(buffer, str, what, value);
    result = BufferGetContent(buffer);

    BufferDestroy(buffer);

    return result;
}

VectorCHARPTR* StringSplit(const char* string, const char* separator)
{
    VectorCHARPTR*  vector;
    char*           next;
    size_t          length;

    CHECK_RETURN(string, NULL, NULL);
    vector = VectorCreateCHARPTR();
    CHECK_RETURN(vector, NULL, NULL);

    if (separator == NULL || *separator == 0)
    {
        VectorPushBackCHARPTR(vector, strdup(string));

        return vector;
    }

    length = strlen(separator);
    while (*string)
    {
        next = strstr(string, separator);
        if (next == NULL)
        {
            VectorPushBackCHARPTR(vector, strdup(string));

            break ;
        }

        VectorPushBackCHARPTR(vector, strndup(string, next - string));
        string = next + length;
    }
    
    return vector;
}