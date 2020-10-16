#include <stdio.h>
#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
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

int solve(const int *a, int n)
{
    int sum = 1;

    for (int i = 0; i < n; i++)
        if (a[i] % 2 == 0)
            sum += a[i];
    if (sum != 1) sum--;
    return sum;
}

int main(void)
{
    int rc = OK, sum, n, a[N];

    rc = input(a, &n);
    if (rc == OK)
    {
        print(a, n);
        sum = solve(a, n);
        if (sum != 1)
            printf("Result is %d", sum);
        else printf("There are no numbers which needed.\nsum = 0");
    }
    else
        printf("Input error!(%d)", rc);
    return rc;
}
