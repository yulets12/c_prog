#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "in_out.h"
#include "errors.h"
#define EPS 0.000001

int matrix_cmpr(double *matrix, double *result, int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (!(fabs(*(matrix + i * m + j) - *(result + i * m + j)) < EPS || (isnan(*(matrix + i * m + j)) != 0 && isnan(*(result + i * m + j)) != 0)))
                return 1;
    return 0;
}

void test_read_matrix(void)
{
    int err_cnt = 0;
    {
        FILE *f;
        double *matrix = NULL;
        int n = 0, m = 0, res_n = 3, res_m = 3;
        double result[] = {1, 74.423, NAN, 0, 0, 0, 1.2, NAN, 3.4};
        f = fopen("in1.txt", "r");
        assert(read_matrix(f, &matrix, &n, &m) == OK);
        if (n != res_n || m != res_m || matrix_cmpr(matrix, result, res_n, res_m))
        {
            err_cnt++;
            printf("Test 1 failed.\n");
        }
        fclose(f);
        free(matrix);
    }
    {
        FILE *f;
        double *matrix = NULL;
        int n = 0, m = 0, res_n = 5, res_m = 2;
        double result[] = {12, 4.5, -9, NAN, 2.54333, NAN, NAN, 2, 3, 5};
        f = fopen("in2.txt", "r");
        assert(read_matrix(f, &matrix, &n, &m) == OK);
        if (n != res_n || m != res_m || matrix_cmpr(matrix, result, res_n, res_m))
        {
            err_cnt++;
            printf("Test 2 failed.\n");
        }
        fclose(f);
        free(matrix);
    }
    {
        FILE *f;
        double *matrix = NULL;
        int n = 0, m = 0, res_n = 0, res_m = 0;
        double result[] = {0};
        f = fopen("empty.txt", "r");
        assert(read_matrix(f, &matrix, &n, &m) == OK);
        if (n != res_n || m != res_m || matrix_cmpr(matrix, result, res_n, res_m))
        {
            err_cnt++;
            printf("Test 3 failed.\n");
        }
        fclose(f);
        free(matrix);
    }
    {
        FILE *f;
        double *matrix = NULL;
        int n = 0, m = 0, res_n = 1, res_m = 1;
        double result[] = {NAN};
        f = fopen("in3.txt", "r");
        assert(read_matrix(f, &matrix, &n, &m) == OK);
        if (n != res_n || m != res_m || matrix_cmpr(matrix, result, res_n, res_m))
        {
            err_cnt++;
            printf("Test 4 failed.\n");
        }
        fclose(f);
        free(matrix);
    }
    printf("READ_MATRIX(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_split(void)
{
    int err_cnt = 0;
    {
        int len = 15, flag = 0;
        char str[] = "12 4 4 gh  gyh\n";
        int result[] = {2, 4, 6, 9, 10, 15};

        if (split(str) != str + len)
            flag = 1;
        for (int i = 0; i < 6; i++)
            if (str[result[i]] != '\0')
                flag = 1;
        if (flag)
        {
            err_cnt++;
            printf("Test 1 failed.\n");
        }
    }
    {
        int len = 1, flag = 0;
        char str[] = "\n";
        int result[] = {0};

        if (split(str) != str + len)
            flag = 1;
        for (int i = 0; i < 1; i++)
            if (str[result[i]] != '\0')
                flag = 1;
        if (flag)
        {
            err_cnt++;
            printf("Test 2 failed.\n");
        }
    }
    {
        int len = 4, flag = 0;
        char str[] = "aaaa";
        int result[] = {0};

        if (split(str) != str + len)
            flag = 1;
        for (int i = 0; i < 0; i++)
            if (str[result[i]] != '\0')
                flag = 1;
        if (flag)
        {
            err_cnt++;
            printf("Test 3 failed.\n");
        }
    }
    printf("SPLIT(): %s", err_cnt ? "FAILED" : "OK");
}

int main(void)
{
    test_read_matrix();
    test_split();

    return 0;
}
