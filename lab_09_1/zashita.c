#include <string.h>
#include <stdio.h>

char*process(char *str)
{
    while (str[0] == ' ')
        str++;
    int len = strlen(str), i = 0;
    while (i < len - 1)
    {
        if (str[i] == ' ' && str[i + 1] == ' ')
        {
            memmove(&str[i], &str[i + 1], len - i - 1);
            len--;
            str[len] = '\0';
        }
        else
            i++;
    }
    if (str[len - 1] == ' ')
        str[len - 1] = '\0';
    return str;
}

void test(void)
{
    int err_cnt = 0;
    {
        char str[] = "abcd";
        char result[] = "abcd";
        char *res;
        res = process(str);
        if (strcmp(result, res))
        {
            printf("Test 1 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "    abcd";
        char result[] = "abcd";
        char *res;
        res = process(str);
        if (strcmp(result, res))
        {
            printf("Test 2 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "abcd       ";
        char result[] = "abcd";
        char *res;
        res = process(str);
        if (strcmp(result, res))
        {
            printf("Test 3 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "ab   cd";
        char result[] = "ab cd";
        char *res;
        res = process(str);
        if (strcmp(result, res))
        {
            printf("Test 4 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "a bcd";
        char result[] = "a bcd";
        char *res;
        res = process(str);
        if (strcmp(result, res))
        {
            printf("Test 5 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "a  bc     d";
        char result[] = "a bc d";
        char *res;
        res = process(str);
        if (strcmp(result, res))
        {
            printf("Test 6 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "    abc  d    ";
        char result[] = "abc d";
        char *res;
        res = process(str);
        if (strcmp(result, res))
        {
            printf("Test 7 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "        ";
        char result[] = "";
        char *res;
        res = process(str);
        if (strcmp(result, res))
        {
            printf("Test 8 failed.\n");
            err_cnt++;
        }
    }
    {
        char str[] = "";
        char result[] = "";
        char *res;
        res = process(str);
        if (strcmp(result, res))
        {
            printf("Test 9 failed.\n");
            err_cnt++;
        }
    }
    printf("PROCESS(): %s\n", err_cnt ? "FAILED" : "OK");
}

int main(void)
{
    test();
    return 0;
}
