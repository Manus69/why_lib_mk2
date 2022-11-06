#ifndef MEMORY_INTERFACE_H
#define MEMORY_INTERFACE_H

void Map(void (*f)(void*), void* ptr, ...);
void Free(void* ptr, ...);

#endif