// #include "array.h"
#include "vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

GetVectorDefinitions(int, INT);
GetVectorDefinitions(void *, PTR);

#define SIZE (1 << 2)

void _print(int* data, size_t length)
{
    for (size_t n = 0; n < length; n ++)
        printf("%d ", data[n]);
    
    printf("\n");
}

static void swap(int* data, size_t lhs, size_t rhs)
{
    int store = data[lhs];
    data[lhs] = data[rhs];
    data[rhs] = store;
}

// long bin_greater(const int* data, long index, size_t length, int ref, int (*cmp)(int, int))
// {
//     long mid = (index + length) / 2;

//     if (!length)
//         return index;
    
//     if (cmp(data[mid], ref) >= 0)
//         return mid;
    
//     return bin_greater(data, index, length - mid - 1, ref, cmp);
// }

// long bin_less(const int* data, long index, size_t length, int ref, int (*cmp)(int, int))
// {
//     long index = length / 2;

//     if (!length)
//         return 0;
    
//     if (cmp(data[index], ref) <= 0)
//         return 0;
    
//     return index + bin_less(data + index + 1, length - index - 1, ref, cmp);
// }

long bin_index(const int* data, long index, size_t length, int reference, int (*cmp)(int, int))
{
    int result;

    long mid = (index + length) / 2;
    result = cmp(data[mid], reference);
    
    if (length == 0)
        return index;
    
    if (result == 0)
        return index;
    
    if (length == 1)
    {
        return result > 0 ? index : index + 1;
    }

    if (result > 0)
        return bin_index(data, index, length - (mid - index + 1), reference, cmp);
    
    return bin_index(data, mid + 1, length - mid - 1, reference, cmp);
}

long find_index(const int* data, long index, size_t length, int (*cmp)(int, int))
{
    while (cmp(data[index], data[index + length]) < 0)
        index ++;
    
    return index;
}

void swap_items(int* data, long target_index, long index)
{
    int store;

    store = data[index];
    while (index > target_index)
    {
        data[index] = data[index - 1];
        index --;
    }
    data[index] = store;

    // memmove(data + 1, data, (index - target_index) * sizeof(int));
    data[target_index] = store;
}
#define N (1 << 27)
// #define N 6

void insert_sort(int* data, size_t length, int (*cmp)(int, int))
{
    long sorted_index;
    long target_index;
    long current;

    current = 1;
    sorted_index = 0;

    // _print(data, length);
    while (current < length)
    {
        if (cmp(data[sorted_index], data[current]) > 0)
        {
            // _print(data, length);

            target_index = find_index(data, 0, sorted_index, cmp);
            // target_index = bin_index(data, 0, sorted_index + 1, data[current], cmp);
            // _print(data, length);
            swap_items(data, target_index, current);
        }

        sorted_index ++;
        current ++;
    }
}

size_t get_pivot(const int* data, size_t length, int (*cmp)(int, int))
{
    size_t pivots[3];

    pivots[0] = rand() % length;
    pivots[1] = rand() % length;
    pivots[2] = rand() % length;

    size_t median = pivots[0];

    if (cmp(data[pivots[0]], data[pivots[1]]) > 0)
    {
        if (cmp(data[pivots[1]], data[pivots[2]]) > 0)
            median = pivots[1];
        else if (cmp(data[pivots[0]], data[pivots[2]]) > 0)
            median = pivots[2];
    }
    else
    {
        if (cmp(data[pivots[1]], data[pivots[2]]) > 0)
            median = pivots[2];
        else if (cmp(data[pivots[0]], data[pivots[2]]) > 0)
            median = pivots[1];
    }
    
    return median;
}

size_t partition(int* data, size_t length, int (*cmp)(int, int))
{
    size_t pivot_index = rand() % length;
    // size_t pivot_index = get_pivot(data, length, cmp);
    long mid_index = -1;

    long index = 0;
    swap(data, pivot_index, length - 1);
    // _print(data, N);
    pivot_index = length - 1;
    while (index < pivot_index)
    {
        if (cmp(data[pivot_index], data[index]) > 0)
        {
            mid_index ++;
            swap(data, index, mid_index);
        }

        index ++;
    }

    mid_index ++;
    swap(data, mid_index, pivot_index);

    return mid_index;
}

void sort(int* data, size_t length, int (*cmp)(int, int))
{
    // _print(data, length);

    if (length < 2) return ;
    // if (length < 50) return insert_sort(data, length, cmp);

    // size_t pivot_index = index + length - 1;

    size_t pivot_index = partition(data, length, cmp);
    // _print(data, length);

    sort(data, pivot_index, cmp);
    sort(data + pivot_index + 1, length - pivot_index - 1, cmp);
}

int cmp(int a, int b)
{
    // return a > b;
    return a - b;
}

int cmp2(int a, int b)
{
    return b - a;
}

void make_heap(int* array, long size, int (*cmp)(int, int));
int extract_top(int* heap, long size, int (*cmp)(int, int));
void merge_sort(int* data, long index, long length, int (*cmp)(int, int));


int main()
{
    // int data[N];

    srand(0);

    int* data = malloc(sizeof(int) * N);
    for (int n = 0; n < N; n ++)
        data[n] = N - n;

    merge_sort(data, 0, N, cmp);
    // sort(data, N, cmp);
    // insert_sort(data, N, cmp);
    // make_heap(data, N, cmp);
    // for (int n = N; n > 0; n --)
    // {
    //     int top = extract_top(data, n, cmp);
    // }
    printf("%d\n", data[N - 1]);
    // _print(data, N);
}