#include <stdlib.h>
#include "functions.h"
#include "errors.h"

/**
 * Считывает строку lineptr длины n из текстогого файла stream.
 * @param lineptr [in/out]
 * @param n [n]
 * @param stream [in]
 * @return Возвращает количество считанных символов.
 */
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream)
{
    if (lineptr == NULL || n == NULL || stream == NULL || (*lineptr != NULL && *n == 0))
        return ERR;
        
    int len, linelen = 0;
    char buf[N + 1];

    while (fgets(buf, sizeof(buf), stream) && (len = my_strlen(buf)) > 0)
    {
        if (*lineptr == NULL || linelen + len + 1 > *n)
        {
            char *ptmp = realloc(*lineptr, linelen + len + 1);
            if (!ptmp)
                return ERR;
            *lineptr = ptmp;
            *n = linelen + len;
        }
        for (int i = 0; i < len; i++)
        {
            (*lineptr)[linelen] = buf[i];
            linelen++;
        }
        if (buf[len - 1] == '\n')
            break;
    }

    if (linelen > 0)
        (*lineptr)[linelen] = '\0';
    else 
        return ERR;

    return linelen;
}

/**
 * Сравнивает строки str1 и str2 на частичное совпадение.
 * @param str1 [in]
 * @param str2 [in]
 * @return Возвращает 1, если одна строка является подстрокой другой строки, иначе - возвращает 0.
 */
int cmpr(const char *str1, const char *str2)
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
            return 0;
        i++;
    }
    return 1;
}

/**
 * Ищет подстроку search в строке и заменяет ее(все вхождения) на replace.
 * @param source [in]
 * @param search [in]
 * @param replace [in]
 * @return Возвращает указатель на строку-результат.
 */
char*str_replace(const char *source, const char *search, const char *replace)
{
    if (source == NULL || search == NULL || replace == NULL)
        return NULL;    
    char *result = NULL;
    int length = 0, reslen = 0, source_len = my_strlen(source), search_len = my_strlen(search), replace_len = my_strlen(replace);

    for (int i = 0; i < source_len;)
        // цикл по строке
    {
        if (cmpr(&source[i], search) == 1)
            // если текущий символ является началом подстроки, которую нужно заменить
        {
            while (length - reslen < replace_len)
                // проверка на количество свободной памяти
            {
                char *ptmp = realloc(result, reslen + STEP); // увеличение результирующей строки
                if (!ptmp)
                    return NULL;
                result = ptmp;
                length += STEP;
            }
            res_append(result, &reslen, replace, replace_len); // добавление в результирующую строку подстроки, на которую заменяем
            i += search_len; // увеличиваем счетчик на длину подстроки, которую нужно заменить
        }
        else
        {
            while (length - reslen < 1)
                // проверка на количество свободной памяти
            {
                char *ptmp = realloc(result, reslen + STEP); // увеличение результирующей строки
                if (!ptmp)
                    return NULL;
                result = ptmp;
                length += STEP;
            }
            result[reslen] = source[i]; // добавление в результирующую строку текущего символа
            reslen++;
            i++; // увеличиваем счетчик
        }
    }
    if (length - reslen < 1)
    {
        char *ptmp = realloc(result, reslen + 1);
        if (!ptmp)
            return NULL;
        result = ptmp;
    }
    result[reslen] = '\0';

    return result;
}

/**
 * Определяет длину строки str.
 * @param str [in]
 * @return Возвращает длину строки.
 */
int my_strlen(const char *str)
{
    int i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

/**
 * Выполняет построчное считывание данных из текстового файла f_in, замену подстроки search на replace и запись результата в файл f_out.
 * @param f_in [in]
 * @param f_out [in]
 * @param search [in]
 * @param replace [in]
 * @return Возвращает ERR_EMPTY, если файл пустой, иначе - возвращает OK.
 */
int process(FILE *f_in, FILE *f_out, const char *search, const char *replace)
{
    char *line = NULL, *result = NULL;
    int k = 0, rc = OK;
    size_t len = 0;
    while (my_getline(&line, &len, f_in) > 0)
    {
        if (!(result = str_replace(line, search, replace)))
        {
            rc = ERR_MEM;
            break;
        }
        fprintf(f_out, "%s", result);
        free(result);
        free(line);
        result = NULL;
        line = NULL;
        len = 0;
        k++;
    }
    free(result);
    free(line);
    if (rc >= 0)
        rc = OK;
    if (rc != ERR_MEM && k == 0)
        rc = ERR_EMPTY;
    return rc;
}

/**
 * Сравнивает строки str1 и str2 на полное совпадение.
 * @param str1 [in]
 * @param str2 [in]
 * @return Возвращает 1, если одна строки равны, иначе - возвращает 0.
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
    return 0;
}

/**
 * Функция добавления в результирующую строку подстроки, на которую заменяем.
 * @param result [out]
 * @param reslen [out]
 * @param replace [in]
 * @param replace_len [in]
 */
void res_append(char *result, int *reslen, const char *replace, int replace_len)
{
    for (int j = 0; j < replace_len; j++)
    {
        result[*reslen] = replace[j];
        (*reslen)++;
    }
}
