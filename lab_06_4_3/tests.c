#include <stdio.h>
#include <assert.h>
#include "in_out.h"
#include "process.h"

void test_input(void)
{
    int err_cnt = 0;
    printf("INPUT\n");
    //not numbers
    {
        FILE *f;
        int a[N];
        int *pbeg = a, *pend = a;

        f = fopen("in_2.txt", "r");
        assert(f != NULL);
        if (input(f, pbeg, &pend) != OK || pbeg != pend)
        {
            printf("Test 1: FAILED\n");
            err_cnt++;
        }
        fclose(f);
    }
    //less than 100
    {
        FILE *f;
        int a[N];
        int *pbeg = a, *pend = a;

        f = fopen("in_3.txt", "r");
        assert(f != NULL);
        if (input(f, pbeg, &pend) != OK)
        {
            printf("Test 2: FAILED\n");
            err_cnt++;
        }
        fclose(f);
    }
    //more than 100
    {
        FILE *f;
        int a[N];
        int *pbeg = a, *pend = a;

        f = fopen("in_5.txt", "r");
        assert(f != NULL);
        if (input(f, pbeg, &pend) != ERR_RANGE)
        {
            printf("Test 3: FAILED\n");
            err_cnt++;
        }
        fclose(f);
    }

    printf("input(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_check(void)
{
    int err_cnt = 0;
     printf("CHECK\n");
    //length of array 1
    {
        int a[1] = {0};
        int *pbeg = a, *pcur = pbeg;


        if (!check(pcur, pbeg))
        {
            printf("Test 1: FAILED\n");
            err_cnt++;
        }
    }
    //different numbers
    {
        int a[5] = {1, 2, 3, 4, 5};
        int *pbeg = a, *pcur = pbeg + 4;


        if (!check(pcur, pbeg))
        {
            printf("Test 2: FAILED\n");
            err_cnt++;
        }
    }
    //last is not different
    {
        int a[7] = {0, 4, 2, 5, 8, 1, 5};
        int *pbeg = a, *pcur = pbeg + 6;


        if (check(pcur, pbeg))
        {
            printf("Test 3: FAILED\n");
            err_cnt++;
        }
    }

    printf("check(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_solve(void)
{
    int err_cnt = 0;
     printf("SOLVE\n");
    //all the numbers are the same
    {
        int a[6] = {0, 0, 0, 0, 0, 0};
        int *pbeg = a, *pend = pbeg + 6;


        if (solve(pend, pbeg) != 1)
        {
            printf("Test 1: FAILED\n");
            err_cnt++;
        }
    }
    //all the numbers are different
    {
        int a[5] = {1, 2, 3, 4, 5};
        int *pbeg = a, *pend = pbeg + 5;


        if (solve(pend, pbeg) != 5)
        {
            printf("Test 2: FAILED\n");
            err_cnt++;
        }
    }
    //there are some numbers which repeat
    {
        int a[8] = {0, 4, 2, 5, 8, 1, 5, 4};
        int *pbeg = a, *pend = pbeg + 8;


        if (solve(pend, pbeg) != 6)
        {
            printf("Test 3: FAILED\n");
            err_cnt++;
        }
    }

    printf("solve(): %s\n", err_cnt ? "FAILED" : "OK");
}

int main(void)
{
    test_input();
    test_check();
    test_solve();
    return 0;
}
