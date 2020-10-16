#include <stdio.h>
#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define EMPTY_ARR 3
#define N 10

int input(int *a, int *n)
{
    printf("Input n: ");
    if (scanf("%d", n) != 1)
        return ERR_IO;
    if ((*n < 0) || (*n > N))
        return ERR_RANGE;
    printf("Input array:\n");
    for (int i = 0; i < *n; i++)
        if (scanf("%d", &a[i]) != 1)
            return ERR_IO;
    printf("\n");
    return OK;
}

void print(const int *a, int n)
{
    printf("Array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

int average(const int *a, int n, float *av)
{
    float sum = 0;
    if (n == 0) return EMPTY_ARR;
    for (int i = 0; i < n; i++)
        sum += a[i];
    *av = sum / n;
    return OK;
}

int solve(const int *a, int *b, int n, float av)
{
    int nb = 0;
    for (int i = 0; i < n; i++)
        if (a[i] > av)
        {
            b[nb] = a[i];
            (nb)++;
        }
    return nb;
}

int main(void)
{
    int rc = OK, n, a[N], b[N], nb;
    float av;

    rc = input(a, &n);
    if (rc == OK)
    {
        print(a, n);
        if (average(a, n, &av) == OK)
        {
            nb = solve(a, b, n, av);
            printf("Result ");
            print(b, nb);
        }
        else printf("Array is empty");
    }
    else
        printf("Input error!(%d)", rc);
    return rc;
}
