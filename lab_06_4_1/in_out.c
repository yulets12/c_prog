#include <stdio.h>
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
    printf("Array:\n");
    while (pbeg < pend)
    {
        printf("%d ", *pbeg);
        pbeg++;
    }
    printf("\n");
}
