#include <assert.h>
#include "err.h"
#include "process.h"

int check(int *x, int n, int *y, int m, int k)
{
    int num = 0;
    assert(n == m);
    
    for (int  i = 0; i < n; i++)
        if (x[i] != y[i])
            num++;
    if (num <= k)
        return 1;
    else
        return 0;
}

int solve(int *x, int n, int *y, int m, int k, int *result)
{
    assert(n > 0 && m > 0);
    assert(k >= 0 && k <= m);
    
    if (n <= m)
        return ERR_RANGE;
    
    for (int i = 0; i < n - m; i++)
        (*result) += check(x+i, m, y, m, k);
    return OK;
}
