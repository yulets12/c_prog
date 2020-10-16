#include <stdio.h>
#include "err.h"
#include "in_out.h"

int input(FILE *f, int *a, int *n)
{
    if (fscanf(f, "%d", n) != 1)
        return ERR_IO;
    if (*n <= 0 || *n > N)
        return ERR_RANGE;
    for (int i = 0; i < *n; i++)
        if (fscanf(f, "%d", &a[i]) != 1)
            return ERR_IO;
    return OK;
}

void output(const int *a, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

