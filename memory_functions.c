#include <stdlib.h>
#include <stdarg.h>

#include "macros.h"

static void _map(void (*f)(void*), void* ptr, va_list* args)
{
    void* current;

    f(ptr);
    while ((current = va_arg(*args, void*)))
    {
        f(current);
    }
}

void Free(void* ptr, ...)
{
    va_list args;

    va_start(args, ptr);
    _map(free, ptr, &args);
    va_end(args);
}

void Map(void (*f)(void*), void* ptr, ...)
{
    va_list args;

    va_start(args, ptr);
    _map(f, ptr, &args);
    va_end(args);
}

void MapRegion(void* ptr, size_t n_items, size_t item_size, void (*f)(void*))
{
    while (n_items)
    {
        f(ptr);
        ptr += item_size;
        n_items --;
    }
}