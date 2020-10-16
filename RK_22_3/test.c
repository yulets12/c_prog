#include <stdio.h>
#include "err.h"
#include "process.h"

void test_check(void)
{
    int k = 1;
    {
        int x[] = {1, 5, 5};
        int y[] = {1, 5, 5};

        if (check(x, 3, y, 3, 0) == 1 )
            printf("Test %d: OK\n", k);
        else
            printf("Test %d: FAILED\n", k);
        k++;
    }
    {
        int x[] = {1, 7, 6, 1};
        int y[] = {2, 7, 3, 1};

        if (check(x, 4, y, 4, 2) == 1 )
            printf("Test %d: OK\n", k);
        else
            printf("Test %d: FAILED\n", k);
        k++;
    }
    {
        int x[] = {1, 5};
        int y[] = {1, 9};

        if (check(x, 2, y, 2, 0) == 0 )
            printf("Test %d: OK\n", k);
        else
            printf("Test %d: FAILED\n", k);
        k++;
    }
    {
        int x[] = {0, 8, 4, 2, 6};
        int y[] = {6, 8, 0, 2, 4};

        if (check(x, 3, y, 3, 1) == 0 )
            printf("Test %d: OK\n", k);
        else
            printf("Test %d: FAILED\n", k);
        k++;
    }
    printf("\n");
}

void test_solve(void)
{
    int k = 1;
    {
        int r = 0;
        int x[] = {1, 5, 5, 8, 6, 5, 5, 6, 8, 5, 1, 6};
        int y[] = {5, 5, 6};

        if (solve(x, 12, y, 3, 1, &r) == OK && r == 4)
            printf("Test %d: OK\n", k);
        else
            printf("Test %d: FAILED\n", k);
        k++;
    }
    {
        int r = 0;
        int x[] = {1, 1, 1, 1, 1};
        int y[] = {1, 1};

        if (solve(x, 5, y, 2, 1, &r) == OK && r == 4)
            printf("Test %d: OK\n", k);
        else
            printf("Test %d: FAILED\n", k);
        k++;
    }
    {
        int r = 0;
        int x[4];
        int y[8];

        if (solve(x, 4, y, 8, 1, &r) == ERR_RANGE)
            printf("Test %d: OK\n", k);
        else
            printf("Test %d: FAILED\n", k);
        k++;
    }
    {
        int r = 0;
        int x[8];
        int y[8];

        if (solve(x, 8, y, 8, 1, &r) == ERR_RANGE)
            printf("Test %d: OK\n", k);
        else
            printf("Test %d: FAILED\n", k);
        k++;
    }
    printf("\n");
}

int main(void)
{
    printf("Tests for check():\n");
    test_check();
    printf("Tests for solve():\n");
    test_solve();
}
