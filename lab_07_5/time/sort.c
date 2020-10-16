#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

/**
 Меняет значение элемента copy_to на значение элемента copy_from.
 * @param copy_from [in]
 * @param copy_to [in]
 * @param size [in]
 */
void copy_element(void *copy_from, void *copy_to, size_t size)
{
    char *from = copy_from;
    char *to = copy_to;

    for (size_t i = 0; i < size; i++)
    {
        *to = *from;
        to++;
        from++;
    }
}

/**
 Сдвигает все элементы от pbeg до pend - 1 на один вправо, при это вставляя элемент pend на место pbeg.
 * @param pbeg [in]
 * @param pend [in]
 * @param size [in]
 */
void move(void *pbeg,void *pend, size_t size)
{
    char buf[size];
    copy_element(pend, buf, size);
    for (char *pcur = (char*)pend; pcur > (char*)pbeg; pcur -= size)
        copy_element(pcur - size, pcur, size);
    copy_element(buf, pbeg, size);
}

/**
 Сортирует массив по возрастанию методом "вставок".
 * @param base [in]
 * @param nmemb [in]
 * @param n [in]
 */
void mysort(void *base, size_t nmemb, size_t n, int (*cmp)(const void*, const void*))
{
    char *pend = (char*) base + nmemb * n;
    //char *last_pj = pend;
    for (char *pi = (char*)base + n; pi < pend; pi += n)
        for (char *pj = (char*)base; pj < pi; pj += n)
            if (cmp(pj, pi) > 0)
                move(pj, pi, n);
}

/**
 Сравнивает два целых числа.
 * @param l [in]
 * @param r [in]
 * @return Возвращает отрицательное число, если правое число больше левого; 0, если числа равны; положительное число, если левое число больше правого.
 */
int cmp_int(const void *l, const void *r)
{
    return (*(int*)l) - (*(int*)r);
}

/**
 Сравнивает два символа.
 * @param l [in]
 * @param r [in]
 * @return Возвращает отрицательное число, если правое число больше левого; 0, если числа равны; положительное число, если левое число больше правого.
 */
int cmp_char(const void *l, const void *r)
{
    return (*(char*)l) - (*(char*)r);
}

/**
 Сравнивает два действительных числа.
 * @param l [in]
 * @param r [in]
 * @return Возвращает отрицательное число, если правое число больше левого; 0, если числа равны; положительное число, если левое число больше правого.
 */
int cmp_double(const void *l, const void *r)
{
    double result = (*(double*)l) - (*(double*)r);
    if (result < 0)
        return NEGATIVE;
    if (result > 0)
        return POSITIVE;
    return ZERO;
}
