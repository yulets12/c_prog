#include <stdio.h>
#define OK 0
#define ERR_IO 1
#define ERR_RANGE 2

void decompose(int n)
{
    int h = 2;

    while ((n > 1) && (h <= n / 2))
    {
        if (n % h == 0)
        {
            printf("%d ", h);
            n /= h;
        }
        else
        {
            h++;
        }
    }
    printf("%d\n", n);
}

int main(void)
{
    int n, rc = OK;

    printf("Input n: ");

    if (scanf("%d", &n) == 1)
    {
        if (n > 0)
        {
            if (n > 1)
            {
                printf("Simple dividers: ");
                decompose(n);
            }
        }
        else
        {
            rc = ERR_RANGE;
            printf("n > zero !\n");
        }
    }
    else
    {
        rc = ERR_IO;
        printf("n is int!\n");
    }
    return rc;
}