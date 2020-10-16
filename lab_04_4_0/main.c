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

void bubble_sort(int *a, int n)
{
    int b;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - 1 - i; j++)
            if (a[j] > a[j + 1])
            {
                b = a[j];
                a[j] = a[j + 1];
                a[j + 1] = b;
            }
}

int main(void)
{
    int rc = OK, n, a[N];

    rc = input(a, &n);
    if (rc == OK)
    {
        print(a, n);
        bubble_sort(a, n);
        printf("Sorted ");
        print(a, n);
    }
    else
        printf("Input error!(%d)", rc);
    return rc;
}
