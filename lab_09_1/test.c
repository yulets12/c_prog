#include <string.h>
#include "functions.h"

/**
 * Сравнивает строки str1 и str2.
 * @param str1 [in]
 * @param str2 [in]
 * @return Возвращает 1, если строки равны, - 0, если нет.
 */
int str_cmpr(const char *str1, const char *str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
            return 0;
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0')
        return 1;
    else
        return 0;
}

void test_strrchr(void)
{
    int err_cnt = 0;
    {
        char str[] = "123456789";
        char smbl = '7';
        if (my_strrchr(str, smbl) != strrchr(str, smbl))
        {
            printf("Test 1 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "";
        char smbl = '7';
        if (my_strrchr(str, smbl) != strrchr(str, smbl))
        {
            printf("Test 2 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "123";
        char smbl = '7';
        if (my_strrchr(str, smbl) != strrchr(str, smbl))
        {
            printf("Test 3 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "aabbccad";
        char smbl = 'a';
        if (my_strrchr(str, smbl) != strrchr(str, smbl))
        {
            printf("Test 4 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "abc";
        char smbl = 'a';
        if (my_strrchr(str, smbl) != strrchr(str, smbl))
        {
            printf("Test 5 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "abc";
        char smbl = 'c';
        if (my_strrchr(str, smbl) != strrchr(str, smbl))
        {
            printf("Test 6 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "abc";
        char smbl = '\0';
        if (my_strrchr(str, smbl) != strrchr(str, smbl))
        {
            printf("Test 7 failed.\n");
            err_cnt++;
        }
    }
    printf("STRRCHR(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_strdup(void)
{
    int err_cnt = 0;
    {
        char str[] = "123456789";
        char *my_res, *res;

        my_res = my_strdup(str);
        res = strdup(str);
        if (str_cmpr(my_res, res) == 0)
        {
            printf("Test 1 failed.\n");
            err_cnt++;
        }
        free(my_res);
        free(res);
    }
    {
        char str[] = "";
        char *my_res, *res;

        my_res = my_strdup(str);
        res = strdup(str);
        if (str_cmpr(my_res, res) == 0)
        {
            printf("Test 2 failed.\n");
            err_cnt++;
        }
        free(my_res);
        free(res);
    }
    {
        char str[] = "aaabbc";
        char *my_res, *res;

        my_res = my_strdup(str);
        res = strdup(str);
        if (str_cmpr(my_res, res) == 0)
        {
            printf("Test 3 failed.\n");
            err_cnt++;
        }
        free(my_res);
        free(res);
    }
    printf("STRDUP(): %s\n", err_cnt ? "FAILED" : "OK");
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

int main(void)
{
    test_strdup();
    test_strrchr();
    test_my_strlen();
    return 0;
}
