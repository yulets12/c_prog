#include <stdio.h>

#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2
#define R 10

int difference(int n)
{
    int max = 0, min = 9, d;

    while (n > 0)
    {
        d = n % R;
        if (d > max) max = d;
        if (d < min) min = d;
        n = n / R;
    }

    return (max - min);
}

int main(void)
{
    int n, dif, rc = OK;

    printf("Input number: ");
    if (scanf("%d", &n) == 1)
    {
        if (n > 0)
        {
            dif = difference(n);
            printf("max_digit - min_digit = %d", dif);
        }
        else
        {
            rc = ERR_RANGE;
            printf("n > zero!");
        }
    }
    else
    {
        rc = ERR_IO;
        printf("n must be int!");
    }
    return rc;
}
