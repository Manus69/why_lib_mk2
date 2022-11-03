// #include "array.h"
#include "vector.h"

#include <stdlib.h>
#include <stdio.h>

GetVectorDefinitions(int, INT);
#define SIZE (1 << 27)

int main()
{
    Vector* vector = VectorCreateINT();

    for (int n = 0; n < SIZE; n ++)
    {
        VectorPushBackINT(vector, n);
    }

    // for (int n = 0; n < SIZE; n ++)
    // {
    //     printf("%d ", VectorGetINT(vector, n));
    // } 
    printf("%d\n", VectorBackINT(vector));

    VectorDestroy(vector);
}