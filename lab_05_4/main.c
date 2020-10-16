#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#define OK 0
#define ERR_WRONG_CMD 1
#define ERR_FILE 2
#define ERR_RANGE 3
#define N 100

int input(FILE *f, int *pbeg, int **pend)
{
    int num;

    if (fscanf(f, "%d", *pend) != 1)
        return OK;
    (*pend)++;
    while ((*pend < pbeg + N) && (fscanf(f, "%d", *pend) == 1))
        (*pend)++;
    if ((*pend == (pbeg + N)) && (fscanf(f, "%d", &num) == 1))
        return ERR_RANGE;
    return OK;
}

void print(const int *pbeg, const int *pend)
{
    assert(pbeg <= pend);

    printf("Array:\n");
    while (pbeg < pend)
    {
        printf("%d ", *pbeg);
        pbeg++;
    }
    printf("\n");
}

bool check(const int *pcur, const int *pbeg)
{
    for (const int *pbcur = pcur - 1; pbeg <= pbcur; pbcur--)
        if (*pbcur == *pcur)
            return false;
    return true;
}
int solve(const int *pbeg, const int *pend)
{
    assert(pbeg <= pend);

    int amount = 0;
    for (const int *pcur = pbeg; pcur < pend; pcur++)
    {
        if (check(pcur, pbeg))
            amount++;
    }
    return amount;
}

int main(int argc, char **argv)
{
    FILE *f;
    int rc = OK, a[N], result;
    int  *pbeg = a, *pend = a;

    if (argc != 2)
    {
        printf("main.exe file_name!!!\n");
        rc = ERR_WRONG_CMD;
    }
    else
    {
        f = fopen(argv[1], "r");
        if (f)
        {
            rc = input(f, pbeg, &pend);
            if ((rc == ERR_RANGE) || (rc == OK))
            {
                if (rc == ERR_RANGE)
                    printf("There are more than %d numbers in the file.\n", N);
                result = solve(pbeg, pend);
                if (result == 0)
                    printf("There are no numbers in the file.");
                else
                {
                    print(pbeg, pend);
                    printf("Amount of different numbers in the file is %d", result);
                }
            }
            else
                printf("Input error");
            fclose(f);
        }
        else
        {
            printf("Can't open the file!!!");
            rc = ERR_FILE;
        }
    }
    return rc;
}
