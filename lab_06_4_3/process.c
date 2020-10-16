#include "process.h"

bool check(const int *pcur, const int *pbeg)
{
    for (const int *pbcur = pcur - 1; pbeg <= pbcur; pbcur--)
        if (*pbcur == *pcur)
            return false;
    return true;
}

int solve(const int *pbeg, const int *pend)
{
    int amount = 0;
    for (const int *pcur = pbeg; pcur < pend; pcur++)
    {
        if(check(pcur, pbeg))
            amount++;
    }
    return amount;
}
