#include <stdlib.h>
#include "errors.h"
#include "in_out.h"

/**
 * Считает количество чисел в файле.
 * @param f [in] файловая переменная
 * @param n [out] количество чисел
 * @return Возвращает количество чисел в файле.
 */
int count_n(FILE *f)
{
    int n = 0, dummy;
    while (fscanf(f, "%d", &dummy) == 1)
        n++;
    return n;
}

/**
 * @brief Считывает массив чисел определенной длины из файла.
 * @param f [in] файловая переменная
 * @param pbeg [in] указатель на начало массива
 * @param pend [in] указатель на за последний элемент массива
 * @return Возвращает OK, если ошибок не было, либо ERR_IO, если данные в файле не соответсвуют требуемому формату.
 */
int read_array(FILE *f, int *pbeg, int *pend)
{
    for (int *pcur = pbeg; pcur < pend; pcur++)
        if (fscanf(f, "%d", pcur) != 1)
            return ERR_IO;
    return OK;
}

/**
 * @brief Считывает массив чисел неопределенной длины из файла.
 * @param f [in] файловая переменная
 * @param pbeg [in] указатель на начало массива
 * @param pend [in] указатель на за последний элемент массива
 * @param rc [out] код ошибки
 * @return Возвращает OK, если ошибок не было; ERR_IO, если данные в файле не соответсвуют требуемому формату; ERR_EMPTY, если в файле нет целых чисел; ERR_MEM, если произошла ошибка при выделении памяти.
 */
int read(FILE *f, int **pbeg, int **pend)
{
    int m, rc = OK;
    int *buf_beg, *buf_end;
    rewind(f);
    m = count_n(f);
    if (m > 0)
    {
        buf_beg = malloc(m * sizeof(int));
        if (buf_beg)
        {
            rewind(f);
            buf_end = buf_beg + m;
            rc = read_array(f, buf_beg, buf_end);
            if (rc == OK)
            {
                *pbeg = buf_beg;
                *pend = buf_end;
            }
            else
                free(buf_beg);
        }
        else
            rc = ERR_MEM;
    }
    else
        rc = ERR_EMPTY;
    return rc;
}

/**
 Сохраняет массив целых чисел в файл, записывая числа в строку, через пробел.
 * @param f [in] файловая переменная
 * @param pbeg [in] указатель на начало массива
 * @param pend [in] указатель на за последний элемент массива
 * @return Возвращает OK, свидетельствуя об успешном сохранении.
 */
int save(FILE *f, const int *pbeg, const int *pend)
{
    for (const int *pcur = pbeg; pcur < pend; pcur++)
        fprintf(f, "%d ", *pcur);
    return OK;
}

/**
 Выводит массив на экран.
 * @param pbeg [in] указатель на начало массива
 * @param pend [in] указатель на за последний элемент массива
 */
void print(const int *pbeg, const int *pend)
{
    printf("Array:\n");
    save(stdout, pbeg, pend);
    printf("\n");
}
