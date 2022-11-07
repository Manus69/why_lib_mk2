#ifndef MEMORY_FUNCTIONS_H
#define MEMORY_FUNCTIONS_H

void Map(void (*f)(void*), void* ptr, ...);
void Free(void* ptr, ...);
void MapRegion(void* ptr, size_t n_items, size_t item_size, void (*f)(void*));

#endif