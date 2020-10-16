#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define N 10
#define R 10

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

bool palindrom(int num)
{
    int k = 0, d1 = 1, d2 = 1;
    if (num < 0)
        return false;
    for (int n = num; n > 0; n /= R)
    {
        k++;
        d2 *= R;
    }
    d2 /= R;
    for (int i = 1; i <= (k / 2); i++)
    {
        if (((num / d1) % R) != ((num / d2) % R))
            return false;
        d1 *= R;
        d2 /= R;
    }
    return true;
}

void solve(int *a, int *n)
{
    int  i_write = 0;
    for (int i_read = 0; i_read < *n; i_read++)
        if (palindrom(a[i_read]) == true)
        {
            a[i_write] = a[i_read];
            i_write++;
        }
    *n = i_write;
}

int main(void)
{
    int rc = OK, n, a[N];

    rc = input(a, &n);
    if (rc == OK)
    {
        print(a, n);
        solve(a, &n);
        printf("Result ");
        print(a, n);
    }
    else
        printf("Input error!(%d)", rc);
    return rc;
}
