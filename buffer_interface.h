#ifndef BUFFER_INTERFACE_H
#define BUFFER_INTERFACE_H

#include <stdlib.h>

typedef struct Buffer Buffer;

Buffer* BufferCreateDefault();
Buffer* BufferCreate(size_t length);
void BufferDestroyContent(Buffer* buffer);
void BufferDestroy(Buffer* buffer);
void BufferDestoryAll(Buffer* buffer);
size_t BufferCapacity(const Buffer* buffer);
size_t BufferLength(const Buffer* buffer);
char BufferGet(const Buffer* buffer, size_t index);
int BufferExpand(Buffer* buffer, size_t length);
int BufferSetLength(Buffer* buffer, const char* str, size_t length);
int BufferSet(Buffer* buffer, const char* str);
char* BufferGetContent(const Buffer* buffer);
char* BufferGetContentCopy(const Buffer* buffer);

#endif