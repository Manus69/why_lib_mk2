#include <stdio.h>
#include <stdlib.h>

void _print(int* data, size_t length);

int cmp_int(int a, int b)
{
    return a - b;
}

static void swap(int* data, long lhs, long rhs)
{
    int store = data[lhs];
    data[lhs] = data[rhs];
    data[rhs] = store;
}

long parent(long index)
{
    return index / 2 - 1;
}

long left_child(long index)
{
    return 2 * index + 1;
}

long right_child(long index)
{
    return 2 * index + 2;
}

void swap_left(int* heap, long index)
{
    long next = left_child(index);
    swap(heap, index, next);
}

void swap_right(int* heap, long index)
{
    long next = right_child(index);
    swap(heap, index, next);
}

long min(const int* heap, long parent, long left, long right, int (*cmp)(int, int))
{
    long smallest = cmp(heap[left], heap[right]) > 0 ? right : left;
    smallest = cmp(heap[parent], heap[smallest]) > 0 ? smallest : parent;

    return smallest;
}

void heapify(int* heap, long size, long index, int (*cmp)(int, int))
{
    long left = left_child(index);
    long right = right_child(index);
    long next;
    
    // _print(heap, size);

    if (index < 0) return ;

    if (left >= size && right >= size)
        return ;

    if (right >= size)
    {
        if (cmp(heap[index], heap[left]) > 0)
            return swap(heap, index, left);
        return ;
    }

    next = min(heap, index, left, right, cmp);
    if (next == index) return ;

    swap(heap, next, index);

    return heapify(heap, size, next, cmp);
}

void restore(int* array, long size, long index, int (*cmp)(int, int))
{
    long parent_index = parent(index);

    if (parent_index == 0) return ;

    if (cmp(array[parent_index], array[index]) > 0)
    {
        swap(array, parent_index, index);
        // return restore(array, parent_index, cmp);
        heapify(array, size, index, cmp);
    }
}

void make_heap(int* array, long size, int (*cmp)(int, int))
{
    long index = size - 1;

    while (index >= 0)
    {
        heapify(array, size, index, cmp);
        // restore(array, size, index, cmp);
        index --;
    }
}

int extract_top(int* heap, long size, int (*cmp)(int, int))
{
    int top = heap[0];
    size --;
    swap(heap, 0, size);
    heapify(heap, size, 0, cmp);

    return top;
}