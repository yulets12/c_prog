#include <assert.h>
#include <stdlib.h>
#include "errors.h"
#include "filter.h"

/**
 Суммирует все элементы массива, кроме нулевого.
 * @param pbeg [in] указатель на начало массива
 * @param pend [in] указатель на за последний элемент массива
 * @param sum [out] результирующая сумма
 * @return Возвращает сумму всех элементов массива, кроме нулевого.
 */
int sum_of_elements(const int *pbeg, const int *pend)
{
    int sum = 0;
    for (const int *pcur = pbeg; pcur < pend; pcur++)
        sum += *pcur;
    return sum;
}

/**
 Находит количество элементов, которые останутся после фильтрации.
 * @param pbeg [in] указатель на начало массива
 * @param pend [in] указатель на за последний элемент массива
 * @param sum [in] сумма элементов массива кроме нулевого
 * @param n [out] количество элементов, которые останутся после фильтрации
 * @return Возвращает количество элементов, которые останутся после фильтрации.
 */
int count_elements(const int *pbeg, const int *pend, int sum)
{
    int n = 0;
    for (const int *pcur = pbeg; pcur < pend - 1; pcur++)
    {
        if (*pcur > sum)
            n++;
        sum -= *(pcur + 1);
    }
    return n;
}

/**
 Копирует из массива элементы, проходящие фильтр, в новый массив.
 * @param pabeg [in] указатель на начало исходного массива
 * @param paend [in] указатель на за последний элемент исходного массива
 * @param pbbeg [in] указатель на начало нового массива
 * @param pbend [in] указатель на за последний элемент нового массива
 * @param sum [in] сумма элементов массива кроме нулевого
 * @param rc [out] код ошибки
 * @return Возвращает OK, если ошибок не было, либо ERR_PARAM, если переданы неверные параметры.
 */
int copy_elements(const int *pabeg, const int *paend, int *pbbeg, int *pbend, int sum)
{
    int *pbcur = pbbeg;
    for (const int *pacur = pabeg; pacur < paend - 1; pacur++)
    {
        if (*pacur > sum)
        {
            if (pbcur < pbend)
            {
                *pbcur = *pacur;
                pbcur++;
            }
            else
                return ERR_PARAM;
        }
        sum -= *(pacur + 1);
    }

    if (pbcur == pbend)
        return OK;
    return ERR_PARAM;
}

/**
 Функция-фильтр. Копирует из массива элементы, которые больше суммы элементов расположенных за ним, в новый массив.
 * @param pabeg [in] указатель на начало исходного массива
 * @param paend [in] указатель на за последний элемент исходного массива
 * @param pbbeg [in] указатель на начало нового массива
 * @param pbend [in] указатель на за последний элемент нового массива
 * @param rc [out] код ошибки
 * @return Возвращает OK, если ошибок не было: ERR_PARAM, если переданы неверные параметры; ERR_EMPTY, если после фильтрации остается пустой массив; ERR_MEM, если произошла ошибка при выделении памяти.
 */
int key(const int *pabeg, const int *paend, int **pbbeg, int **pbend)
{
    int n, rc = OK, sum;
    if (pabeg != NULL && paend != NULL && pabeg < paend)
    {
        sum = sum_of_elements(pabeg + 1, paend);
        n = count_elements(pabeg, paend, sum);
        if (n > 0)
        {
            int *buf_beg = malloc(n * sizeof(int));
            if (buf_beg)
            {
                int *buf_end = buf_beg + n;
                int tmp = copy_elements(pabeg, paend, buf_beg, buf_end, sum);
                assert(tmp == OK);
                *pbbeg = buf_beg;
                *pbend = buf_end;
            }
            else
                rc = ERR_MEM;
        }
        else
            rc = ERR_EMPTY;
    }
    else
        rc = ERR_PARAM;
    return rc;
}
