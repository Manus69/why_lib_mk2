#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void _print(int* data, size_t length);

void _merge(int* target, const int* lhs, \
        const int* rhs, long lhs_length, long rhs_length, int (*cmp)(int, int))
{
    if (lhs_length < 0 && rhs_length < 0)
        return ;
    
    while (1)
    {
        if (lhs_length == 0)
        {
            memcpy(target, rhs, rhs_length * sizeof(int));
            return ;
        }
        if (rhs_length == 0)
        {
            memcpy(target, lhs, lhs_length * sizeof(int));
            return ;
        }

        if (cmp(*lhs, *rhs) > 0)
        {
            *target = *rhs;
            rhs ++;
            rhs_length --;
        }
        else
        {
            *target = *lhs;
            lhs ++;
            lhs_length --;
        }

        target ++;
    }
}

long _get_length(long length, long frame_size)
{
    return length >= frame_size ? frame_size : length;
}

void _pass(const int* source, int* target, long frame_size, long length, int (*cmp)(int, int))
{
    int* rhs;
    int* lhs;
    long lhs_length;
    long rhs_length;
    long remaining;

    lhs = (int *)source;
    remaining = length;

    while (remaining > 0)
    {
        lhs_length = _get_length(remaining, frame_size);
        remaining -= lhs_length;
        rhs = lhs + lhs_length; 
        rhs_length = _get_length(remaining, frame_size);
        remaining -= rhs_length;

        _merge(target, lhs, rhs, lhs_length, rhs_length, cmp);
        
        target += (lhs_length + rhs_length);
        lhs += (lhs_length + rhs_length);
    }
    
}

void merge_sort(int* data, long index, long length, int (*cmp)(int, int))
{
    int* buffer = malloc(sizeof(int) * length);
    int count = 0;
    int n_iterations = log2(length);
    n_iterations = log2(length) - n_iterations ? n_iterations + 1 : n_iterations;
    int frame_size = 1;

    while (count < n_iterations)
    {
        if (!(count % 2))
        {
            // _print(data + index, length);
            _pass(data + index, buffer, frame_size, length, cmp);
        }
        else
        {
            // _print(buffer, length);
            _pass(buffer, data + index, frame_size, length, cmp);
        }

        frame_size *= 2;
        count ++;
    }

    if (n_iterations % 2)
        memcpy(data + index, buffer, sizeof(int) * length);

    free(buffer);
}
