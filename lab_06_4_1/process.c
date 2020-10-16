#include <stdio.h>

int check(const int *pcur, const int *pbeg)
{
    for (const int *pbcur = pcur - 1; pbeg <= pbcur; pbcur--)
        if (*pbcur == *pcur)
            return 0;
    return 1;
}

int solve(const int *pbeg, const int *pend)
{
    int amount = 0, k;
    for (const int *pcur = pbeg; pcur < pend; pcur++)
    {
        k = check(pcur, pbeg);
        if (k == 1)
            amount++;
    }
    return amount;
}
