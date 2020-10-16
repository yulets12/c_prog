#include "functions.h"

/**
 * Ищет последнее вхождение символа symbol в строку string.
 * @param string [in]
 * @param symbol [in]
 * @return Возвращает указатель на последнее вхождение символа в строке string.
 */
const char*my_strrchr(const char *string, int symbol)
{
    const char *ptr = NULL;
    int i = 0;
    while (string[i] != '\0')
    {
        if (string[i] == symbol)
            ptr = string + i;
        i++;
    }
    if (symbol == '\0')
        ptr = string + i;

    return ptr;
}

/**
 * Дублирует строку str с выделением памяти.
 * @param str [in]
 * @return Возвращает указатель на дублированную строку.
 */
char*my_strdup(char *str)
{
    char *res_str = NULL;
    int len = my_strlen(str);
        
    res_str = malloc(len + 1);
    if (!res_str)
        return NULL;

    for (int i = 0; i < len; i++)
        res_str[i] = str[i];
    res_str[len] = '\0';

    return res_str;
}

int my_strlen(char *str)
{
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}
