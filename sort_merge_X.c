#include "template_interface.h"
#include "macros.h"
#include "typedefs.h"

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

static void _merge(XYPE* target,
                XYPE* lhs,
                XYPE* rhs,
                size_t lhs_length, 
                size_t rhs_length, 
                int (*cmp)(const XYPE, const XYPE))
{
    while (true)
    {
        if (lhs_length == 0)
        {
            return (void)memcpy(target, rhs, rhs_length * sizeof(XYPE));
        }
        if (rhs_length == 0)
        {
            return (void)memcpy(target, lhs, lhs_length * sizeof(XYPE));
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

static size_t _get_length(size_t length, size_t frame_size)
{
    return length >= frame_size ? frame_size : length;
}

static void _pass(XYPE* source, 
                XYPE* target, 
                size_t frame_size, 
                size_t length, 
                int (*cmp)(const XYPE, const XYPE))
{
    XYPE*   rhs;
    XYPE*   lhs;
    size_t  lhs_length;
    size_t  rhs_length;
    size_t  remaining;

    lhs = source;
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

void MergeSort_X(XYPE* data, size_t index, size_t length, int (*cmp)(const XYPE, const XYPE))
{
    XYPE*   buffer;
    size_t  count;
    size_t  n_iterations;
    size_t  frame_size;

    buffer = malloc(sizeof(XYPE) * length);
    CHECK_RETURN(buffer, NULL, (void)0);

    n_iterations = log2(length);
    n_iterations = log2(length) - n_iterations ? n_iterations + 1 : n_iterations;
    count = 0;
    frame_size = 1;

    while (count < n_iterations)
    {
        if (!(count % 2))
        {
            _pass(data + index, buffer, frame_size, length, cmp);
        }
        else
        {
            _pass(buffer, data + index, frame_size, length, cmp);
        }

        frame_size *= 2;
        count ++;
    }

    if (n_iterations % 2)
        memcpy(data + index, buffer, sizeof(XYPE) * length);

    free(buffer);
}