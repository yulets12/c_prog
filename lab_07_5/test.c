#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "sort.h"
#include "filter.h"
#include "in_out.h"
#include "errors.h"
#define EPS 0.000001

/**
 Поэлементно сравнивает массивы.
 * @param a [in] указатель на 1 массив
 * @param b [in] указатель на 2 массив
 * @param n [in] количество элементов
 * @return Возвращает 0, если массивы равны; 0, если нет.
 */
int cmp_arr(int *a, int *b, int n)
{
    for (int i = 0; i < n; i++)
        if (b[i] != a[i])
            return 1;
    return 0;
}

void test_count_n(void)
{
    int err_cnt = 0;
    printf("COUNT_N:\n");
    //empty file
    {
        FILE *f;
        int n = 0;
        f = fopen("tests/in_3.txt", "r");
        assert(f != NULL);
        if (count_n(f) != n)
        {
            printf("Test 1: FAILED\n");
            err_cnt++;
        }
        fclose(f);
    }
    //not empty file
    {
        FILE *f;
        int n = 9;
        f = fopen("tests/in_2.txt", "r");
        assert(f != NULL);
        if (count_n(f) != n)
        {
            printf("Test 2: FAILED\n");
            err_cnt++;
        }
        fclose(f);
    }
    printf("count_n(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_read_array(void)
{
    int err_cnt = 0;
    printf("READ_ARRAY:\n");
    //only numbers
    {
        int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int b[9];
        int n = 9;
        FILE *f;

        f = fopen("tests/in_2.txt", "r");
        assert(f != NULL);
        if (read_array(f, b, b + n) == OK)
        {
            if (cmp_arr(a, b, n) == 1)
            {
                printf("Test 1: FAILED\n");
                err_cnt++;
            }
        }
        else
        {
            printf("Test 1: FAILED\n");
            err_cnt++;
        }
        fclose(f);
    }
    //not numbers
    {
        int b[9];
        int n = 9;
        FILE *f;
        f = fopen("tests/in_4.txt", "r");
        assert(f != NULL);
        if (read_array(f, b, b + n) != ERR_IO)
        {
            printf("Test 2: FAILED\n");
            err_cnt++;
        }
        fclose(f);
    }
    //not only numbers
    {
        int b[9];
        int n = 9;
        FILE *f;
        f = fopen("tests/in_5.txt", "r");
        assert(f != NULL);
        if (read_array(f, b, b + n) != ERR_IO)
        {
            printf("Test 3: FAILED\n");
            err_cnt++;
        }
        fclose(f);
    }

    printf("read_array(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_read(void)
{
    int err_cnt = 0;
    printf("READ:\n");
    //empty file
    {
        int *pbeg = NULL, *pend = NULL;
        FILE *f;
        f = fopen("tests/in_3.txt", "r");
        assert(f != NULL);
        if (read(f, &pbeg, &pend) != ERR_EMPTY)
        {
            printf("Test 1: FAILED\n");
            err_cnt++;
        }
        fclose(f);
    }
    //correct file
    {
        int a[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int n = 9;
        int *pbeg = NULL, *pend = NULL;

        FILE *f;
        f = fopen("tests/in_2.txt", "r");
        assert(f != NULL);
        if (read(f, &pbeg, &pend) == OK)
        {
            if (cmp_arr(a, pbeg, n) == 1)
            {
                printf("Test 2: FAILED\n");
                err_cnt++;
            }
        }
        else
        {
            printf("Test 2: FAILED\n");
            err_cnt++;
        }
        fclose(f);
        free(pbeg);
    }
    //not numbers
    {
        int *pbeg = NULL, *pend = NULL;
        FILE *f;
        f = fopen("tests/in_4.txt", "r");
        assert(f != NULL);
        if (read(f, &pbeg, &pend) != ERR_EMPTY)
        {
            printf("Test 3: FAILED\n");
            err_cnt++;
        }
        fclose(f);
        free(pbeg);
    }
    printf("read(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_copy_element(void)
{
    int err_cnt = 0;
    printf("SWAP:\n");
    //int
    {
        int from = 10, to = 20;
        size_t size = sizeof(int);
        copy_element(&from, &to, size);
        if (to != from)
        {
            printf("Test 1: FAILED\n");
            err_cnt++;
        }
    }
    //double
    {
        double from = 10.345, to = 20.543;
        size_t size = sizeof(double);
        copy_element(&from, &to, size);
        if (to != from)
        {
            printf("Test 2: FAILED\n");
            err_cnt++;
        }
    }
    //char
    {
        char *from = "a", *to = "b";
        size_t size = sizeof(char);
        copy_element(&from, &to, size);
        if (to != from)
        {
            printf("Test 3: FAILED\n");
            err_cnt++;
        }
    }

    printf("swap(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_mysort(void)
{
    int err_cnt = 0;
    printf("MYSORT:\n");
    //->
    {
        int a[] = { 1, 2, 3, 4, 5, 6, 7 };
        int sorted[] = { 1, 2, 3, 4, 5, 6, 7 };
        int nmemb = sizeof(a) / sizeof(a[0]);
        size_t n = sizeof(int);
        mysort(a, nmemb, n, cmp_int);
        if (cmp_arr(a, sorted, nmemb) == 1)
        {
            printf("Test 1: FAILED\n");
            err_cnt++;
        }
    }
    //<-
    {
        int a[] = { 7, 6, 5, 4, 3, 2, 1 };
        int sorted[] = { 1, 2, 3, 4, 5, 6, 7 };
        int nmemb = sizeof(a) / sizeof(a[0]);
        size_t n = sizeof(int);
        mysort(a, nmemb, n, cmp_int);
        if (cmp_arr(a, sorted, nmemb) == 1)
        {
            printf("Test 2: FAILED\n");
            err_cnt++;
        }
    }
    //random
    {
        int a[] = { 2, 3, -10, 0, -4, 20 };
        int sorted[] = { -10, -4, 0, 2, 3, 20 };
        int nmemb = sizeof(a) / sizeof(a[0]);
        size_t n = sizeof(int);
        mysort(a, nmemb, n, cmp_int);
        if (cmp_arr(a, sorted, nmemb) == 1)
        {
            printf("Test 3: FAILED\n");
            err_cnt++;
        }
    }
    //all the elements are the same
    {
        int a[] = { 0, 0, 0, 0, 0, 0 };
        int sorted[] = { 0, 0, 0, 0, 0, 0 };
        int nmemb = sizeof(a) / sizeof(a[0]);
        size_t n = sizeof(int);
        mysort(a, nmemb, n, cmp_int);
        for (int i = 0; i < nmemb; i++)
            if (a[i] != sorted[i])
            {
                printf("Test 4: FAILED\n");
                err_cnt++;
                break;
            }
    }
    //some elements are the same
    {
        int a[] = { 0, 12, 0, 0, -3, -24 };
        int sorted[] = { -24, -3, 0, 0, 0, 12 };
        int nmemb = sizeof(a) / sizeof(a[0]);
        size_t n = sizeof(int);
        mysort(a, nmemb, n, cmp_int);
        if (cmp_arr(a, sorted, nmemb) == 1)
        {
            printf("Test 5: FAILED\n");
            err_cnt++;
        }
    }
    //<- 2 elements
    {
        int a[] = { 5, 1 };
        int sorted[] = { 1, 5 };
        int nmemb = sizeof(a) / sizeof(a[0]);
        size_t n = sizeof(int);
        mysort(a, nmemb, n, cmp_int);
        if (cmp_arr(a, sorted, nmemb) == 1)
        {
            printf("Test 6: FAILED\n");
            err_cnt++;
        }
    }
    //-> 2 elements
    {
        int a[] = { 0, 3 };
        int sorted[] = { 0, 3 };
        int nmemb = sizeof(a) / sizeof(a[0]);
        size_t n = sizeof(int);
        mysort(a, nmemb, n, cmp_int);
        if (cmp_arr(a, sorted, nmemb) == 1)
        {
            printf("Test 7: FAILED\n");
            err_cnt++;
        }
    }
    //1 element
    {
        int a[] = { 11 };
        int sorted[] = { 11 };
        int nmemb = sizeof(a) / sizeof(a[0]);
        size_t n = sizeof(int);
        mysort(a, nmemb, n, cmp_int);
        if (cmp_arr(a, sorted, nmemb) == 1)
        {
            printf("Test 8: FAILED\n");
            err_cnt++;
        }
    }
    //empty array
    {
        int a[] = { 0 };
        int sorted[] = { 0 };
        int nmemb = 0;
        size_t n = sizeof(int);
        mysort(a, nmemb, n, cmp_int);
        if (cmp_arr(a, sorted, nmemb) == 1)
        {
            printf("Test 9: FAILED\n");
            err_cnt++;
        }
    } 
    //double array
    {
        double a[] = { 0.5432, -4.1 , 12.99, 12.77 };
        double sorted[] = { -4.1, 0.5432, 12.77, 12.99 };
        int nmemb = 4;
        size_t n = sizeof(double);
        mysort(a, nmemb, n, cmp_double);
        for (int i = 0; i < nmemb; i++)
            if (fabs(sorted[i] - a[i]) > EPS)
            {
                printf("Test 10: FAILED\n");
                err_cnt++;
                break;
            }
    }
    //char array
    {
        char a[] = { 'c', 'f', 'b', 'a' };
        char sorted[] = { 'a', 'b', 'c', 'f' };
        int nmemb = 4;
        size_t n = sizeof(char);
        mysort(a, nmemb, n, cmp_char);
        for (int i = 0; i < nmemb; i++)
            if (sorted[i] != a[i])
            {
                printf("Test 11: FAILED\n");
                err_cnt++;
                break;
            }
    }
    printf("mysort(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_sum_of_elements(void)
{
    int err_cnt = 0;
    printf("SUM_OF_ELEMENTS:\n");
    {
        int a[] = { 2, 3, -10, 0, -4, 20 };
        int res = 9;
        if (sum_of_elements(a + 1, a + 6) != res)
        {
            printf("Test 1: FAILED\n");
            err_cnt++;
        }
    }
    {
        int a[] = { 0, -4, -3, -2 };
        int res = -9;
        if (sum_of_elements(a + 1, a + 4) != res)
        {
            printf("Test 2: FAILED\n");
            err_cnt++;
        }
    }
    {
        int a[] = { 2 };
        int res = 0;
        if (sum_of_elements(a + 6, a + 6) != res)
        {
            printf("Test 3: FAILED\n");
            err_cnt++;
        }
    }
    printf("sum_of_elements(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_count_elements(void)
{
    int err_cnt = 0;
    printf("COUNT_ELEMENTS:\n");
    {
        int a[] = { 1, 2, 3, 4, 5 };
        int l = 5;
        int n = 0;
        int sum = 14;
        if (count_elements(a, a + l, sum) != n)
        {
            printf("Test 1: FAILED\n");
            err_cnt++;
        }
    }
    {
        int a[] = { 1 };
        int l = 1;
        int n = 0;
        int sum = 0;
        if (count_elements(a, a + l, sum) != n)
        {
            printf("Test 2: FAILED\n");
            err_cnt++;
        }
    }
    {
        int a[] = { 100, 50, 25, 12, 0 };
        int l = 5;
        int n = 4;
        int sum = 87;
        if (count_elements(a, a + l, sum) != n)
        {
            printf("Test 3: FAILED\n");
            err_cnt++;
        }
    }
    {
        int a[] = { 10, 50, -2, 12, 0, -4 };
        int l = 6;
        int n = 3;
        int sum = 56;
        if (count_elements(a, a + l, sum) != n)
        {
            printf("Test 4: FAILED\n");
            err_cnt++;
        }
    }

    printf("count_elements(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_key(void)
{
    int err_cnt = 0;
    printf("KEY:\n");
    {
        int a[] = { 11 };
        int na = sizeof(a) / sizeof(a[0]);
        int *pbbeg = NULL, *pbend = NULL;
        if (key(a, a + na, &pbbeg, &pbend) != ERR_EMPTY)
        {
            printf("Test 1: FAILED\n");
            err_cnt++;
        }
    }
    {
        int a[] = { 10, 50, -2, 12, 0, -4 };
        int filtered[] = { 50, 12, 0 };
        int nf = 3;
        int na = sizeof(a) / sizeof(a[0]);
        int *pbbeg = NULL, *pbend = NULL;
        if (key(a, a + na, &pbbeg, &pbend) == OK)
        {
            if (cmp_arr(filtered, pbbeg, nf) == 1)
            {
                printf("Test 2: FAILED\n");
                err_cnt++;
            }
            free(pbbeg);
        }
        else
        {
            printf("Test 2: FAILED\n");
            err_cnt++;
        }
    }
    {
        int a[] = { 100, 50, 25, 12, 0 };
        int filtered[] = { 100, 50, 25, 12 };
        int nf = 4;
        int na = sizeof(a) / sizeof(a[0]);
        int *pbbeg = NULL, *pbend = NULL;
        if (key(a, a + na, &pbbeg, &pbend) == OK)
        {
            if (cmp_arr(filtered, pbbeg, nf) == 1)
            {
                printf("Test 3: FAILED\n");
                err_cnt++;
            }
            free(pbbeg);
        }
        else
        {
            printf("Test 3: FAILED\n");
            err_cnt++;
        }
    }
    {
        int a[] = { 1, 2, 3, 4, 5 };
        int na = sizeof(a) / sizeof(a[0]);
        int *pbbeg = NULL, *pbend = NULL;
        if (key(a, a + na, &pbbeg, &pbend) != ERR_EMPTY)
        {
            printf("Test 4: FAILED\n");
            err_cnt++;
        }
    }
    {
        int *pabeg = NULL, *paend = NULL;
        int *pbbeg = NULL, *pbend = NULL;
        if (key(pabeg, paend, &pbbeg, &pbend) != ERR_PARAM)
        {
            printf("Test 5: FAILED\n");
            err_cnt++;
        }
    }
    {
        int a[] = { 1 };
        int *pabeg = a, *paend = a;
        int *pbbeg = NULL, *pbend = NULL;
        if (key(pabeg, paend, &pbbeg, &pbend) != ERR_PARAM)
        {
            printf("Test 6: FAILED\n");
            err_cnt++;
        }
    }
    printf("key(): %s\n", err_cnt ? "FAILED" : "OK");
}

int main(void)
{
    test_count_n();
    test_read_array();
    test_read();
    test_copy_element();
    test_mysort();
    test_sum_of_elements();
    test_count_elements();
    test_key();

    return 0;
}
