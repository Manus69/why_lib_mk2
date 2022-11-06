#ifndef MEMORY_FUNCTIONS_H
#define MEMORY_FUNCTIONS_H

void Map(void (*f)(void*), void* ptr, ...);
void Free(void* ptr, ...);

#endif