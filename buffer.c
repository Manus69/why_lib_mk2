#include "buffer.h"
#include "buffer_interface.h"
#include "macros.h"

#include <string.h>

#define LENGTH_DEFAULT (1 << 10)

Buffer* BufferCreate(size_t length)
{
    Buffer* buffer;

    buffer = malloc(sizeof(*buffer));
    CHECK_RETURN(buffer, NULL, NULL);

    if (!(buffer->data = malloc(length + 1)))
        RETURN_AFTER(free(buffer), NULL);

    buffer->capacity = length;
    buffer->index = 0;

    return buffer;
}

Buffer* BufferCreateDefault()
{
    return BufferCreate(LENGTH_DEFAULT);
}

void BufferDestroyContent(Buffer* buffer)
{
    if (buffer)
        free(buffer->data);
}

void BufferDestroy(Buffer* buffer)
{
    if (buffer)
    {
        free(buffer);
    }
}

void BufferDestoryAll(Buffer* buffer)
{
    if (buffer)
    {
        free(buffer->data);
        free(buffer);
    }
}

char BufferGet(const Buffer* buffer, size_t index)
{
    return buffer->data[index];
}

int BufferExpand(Buffer* buffer, size_t length)
{
    char* new_data;

    length = length > (2 * buffer->capacity) ? length : (2 * buffer->capacity);
    length ++;
    new_data = realloc(buffer->data, buffer->capacity + length);
    CHECK_RETURN(new_data, NULL, NOT_OK);
    buffer->data = new_data;
    buffer->capacity += length;

    return OK;
}

size_t BufferCapacity(const Buffer* buffer)
{
    return buffer->capacity - buffer->index;
}

size_t BufferLength(const Buffer* buffer)
{
    return buffer->index;
}

int BufferSetLength(Buffer* buffer, const char* str, size_t length)
{

    if ((BufferCapacity(buffer) < length) && (BufferExpand(buffer, length) == NOT_OK))
        return NOT_OK;

    memcpy(buffer->data + buffer->index, str, length);
    buffer->index += length;

    return OK;   
}

int BufferSet(Buffer* buffer, const char* str)
{
    return BufferSetLength(buffer, str, strlen(str));
}

char* BufferGetContent(const Buffer* buffer)
{
    buffer->data[buffer->index] = 0;

    return buffer->data;
}

char* BufferGetContentCopy(const Buffer* buffer)
{
    buffer->data[buffer->index] = 0;

    return strdup(buffer->data);
}