#include "string_functions.h"
#include "buffer_interface.h"
#include "macros.h"

#include <string.h>

static void _replace(Buffer* buffer, const char* str, const char* what, const char* value)
{
    char* next;

    if (*str == 0)
        return ;
    
    next = strstr(str, what);
    
    if (next == NULL)
    {
        BufferSet(buffer, str);
        return ;
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

    if (*what == 0)
        return NULL;
    
    buffer = BufferCreate(strlen(str));
    CHECK_RETURN(buffer, NULL, NULL);

    _replace(buffer, str, what, value);
    result = BufferGetContent(buffer);

    BufferDestroy(buffer);

    return result;
}