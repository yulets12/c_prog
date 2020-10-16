#include <stdlib.h>
#include "functions.h"
#include "errors.h"

void test_cmpr(void)
{
    int err_cnt = 0;
    {
        char str1[] = "abcde";
        char str2[] = "abcde";
        if (cmpr(str1, str2) != 1)
        {
            printf("Test 1 failed.\n");
            err_cnt++;
        }
    }
    {
        char str1[] = "abcde";
        char str2[] = "abc";
        if (cmpr(str1, str2) != 1)
        {
            printf("Test 2 failed.\n");
            err_cnt++;
        }
    }
    {
        char str1[] = "abcde";
        char str2[] = "fffff";
        if (cmpr(str1, str2) != 0)
        {
            printf("Test 3 failed.\n");
            err_cnt++;
        }
    }
    {
        char str1[] = "abcde";
        char str2[] = "ea";
        if (cmpr(str1, str2) != 0)
        {
            printf("Test 4 failed.\n");
            err_cnt++;
        }
    }
    printf("CMPR(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_str_cmpr(void)
{
    int err_cnt = 0;
    {
        char str1[] = "abcde";
        char str2[] = "abcde";
        if (str_cmpr(str1, str2) != 1)
        {
            printf("Test 1 failed.\n");
            err_cnt++;
        }
    }
    {
        char str1[] = "abcde";
        char str2[] = "abc";
        if (str_cmpr(str1, str2) != 0)
        {
            printf("Test 2 failed.\n");
            err_cnt++;
        }
    }
    {
        char str1[] = "abcde";
        char str2[] = "12345";
        if (str_cmpr(str1, str2) != 0)
        {
            printf("Test 3 failed.\n");
            err_cnt++;
        }
    }
    {
        char str1[] = "00";
        char str2[] = "acde";
        if (str_cmpr(str1, str2) != 0)
        {
            printf("Test 4 failed.\n");
            err_cnt++;
        }
    }
    printf("STR_CMPR(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_my_strlen(void)
{
    int err_cnt = 0;
    {
        char str[] = "abcde";
        int len = 5;
        if (my_strlen(str) != len)
        {
            printf("Test 1 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "";
        int len = 0;
        if (my_strlen(str) != len)
        {
            printf("Test 2 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "abc\n";
        int len = 4;
        if (my_strlen(str) != len)
        {
            printf("Test 3 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "\n";
        int len = 1;
        if (my_strlen(str) != len)
        {
            printf("Test 4 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "\0";
        int len = 0;
        if (my_strlen(str) != len)
        {
            printf("Test 5 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "abcde\0";
        int len = 5;
        if (my_strlen(str) != len)
        {
            printf("Test 6 failed.\n");
            err_cnt++;
        }
    }
    printf("MY_STRLEN(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_my_getline(void)
{
    int err_cnt = 0;
    {
        FILE *f;
        char *line = NULL;
        size_t len = 0;
        f = fopen("tests/empty.txt", "r");
        if (my_getline(&line, &len, f) != 0)
        {
            printf("Test 1 failed.\n");
            err_cnt++;
        }
        fclose(f);
        free(line);
    }
    {
        FILE *f;
        char *line = NULL;
        char result[] = "1234567890\n";
        int reslen = 11;
        size_t len = 0;
        f = fopen("tests/in1.txt", "r");
        if (my_getline(&line, &len, f) != reslen || str_cmpr(line, result) != 1)
        {
            printf("Test 2 failed.\n");
            err_cnt++;
        }
        fclose(f);
        free(line);
    }
    {
        FILE *f;
        char *line = NULL;
        char result[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        int reslen = 200;
        size_t len = 0;
        f = fopen("tests/in2.txt", "r");
        if (my_getline(&line, &len, f) != reslen || str_cmpr(line, result) != 1)
        {
            printf("Test 3 failed.\n");
            err_cnt++;
        }
        fclose(f);
        free(line);
    }
    {
        FILE *f;
        char *line = malloc(20);
        char result[] = "1234567890\n";
        int reslen = 11;
        size_t len = 20;
        f = fopen("tests/in1.txt", "r");
        if (my_getline(&line, &len, f) != reslen || str_cmpr(line, result) != 1)
        {
            printf("Test 4 failed.\n");
            err_cnt++;
        }
        fclose(f);
        free(line);
    }
    // на этом тесте происходит ошибка памяти
    {
        FILE *f;
        char *line = malloc(50);
        char result[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        int reslen = 200;
        size_t len = 50;
        f = fopen("tests/in2.txt", "r");
        if (my_getline(&line, &len, f) != reslen || str_cmpr(line, result) != 1)
        {
            printf("Test 5 failed.\n");
            err_cnt++;
        }
        fclose(f);
        free(line);
    }
    {
        FILE *f;
        char *line = NULL;
        size_t len = 20;
        f = fopen("tests/empty.txt", "r");
        if (my_getline(&line, &len, f) != ERR_ARGS)
        {
            printf("Test 6 failed.\n");
            err_cnt++;
        }
        fclose(f);
        free(line);
    }
    {
        FILE *f;
        char *line = malloc(20);
        size_t len = 0;
        f = fopen("tests/empty.txt", "r");
        if (my_getline(&line, &len, f) != ERR_ARGS)
        {
            printf("Test 7 failed.\n");
            err_cnt++;
        }
        fclose(f);
        free(line);
    }
    {
        FILE *f;
        char *line = malloc(300);
        char result[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        int reslen = 200;
        size_t len = 300;
        f = fopen("tests/in2.txt", "r");
        if (my_getline(&line, &len, f) != reslen || str_cmpr(line, result) != 1)
        {
            printf("Test 8 failed.\n");
            err_cnt++;
        }
        fclose(f);
        free(line);
    }
    printf("MY_GETLINE(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_str_replace(void)
{
    int err_cnt = 0;
    {
        char source[] = "aabbccdd";
        char search[] = "ab";
        char replace[] = "cc";
        char *result = NULL, my_result[] = "accbccdd";
        if (!(result = str_replace(source, search, replace)) || str_cmpr(result, my_result) != 1)
        {
            printf("Test 1 failed.\n");
            err_cnt++;
        }
        free(result);
    }
    {
        char source[] = "abcdefg";
        char search[] = "ab";
        char replace[] = "AB";
        char *result = NULL, my_result[] = "ABcdefg";
        if (!(result = str_replace(source, search, replace)) || str_cmpr(result, my_result) != 1)
        {
            printf("Test 2 failed.\n");
            err_cnt++;
        }
        free(result);
    }
    {
        char source[] = "abcdefg";
        char search[] = "w";
        char replace[] = "v";
        char *result = NULL, my_result[] = "abcdefg";
        if (!(result = str_replace(source, search, replace)) || str_cmpr(result, my_result) != 1)
        {
            printf("Test 3 failed.\n");
            err_cnt++;
        }
        free(result);
    }
    {
        char source[] = "abcdefg";
        char search[] = "c1";
        char replace[] = "b4";
        char *result = NULL, my_result[] = "abcdefg";
        if (!(result = str_replace(source, search, replace)) || str_cmpr(result, my_result) != 1)
        {
            printf("Test 4 failed.\n");
            err_cnt++;
        }
        free(result);
    }
    printf("STR_REPLACE(): %s\n", err_cnt ? "FAILED" : "OK");
}

int main(void)
{
    test_cmpr();
    test_str_cmpr();
    test_my_strlen();
    test_my_getline();
    test_str_replace();

    return 0;
}
