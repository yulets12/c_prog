#include <stdlib.h>
#include "sort.h"
#include "in_out.h"

/**
 Меняет значение элемента copy_to на значение элемента copy_from.
 * @param copy_from [in]
 * @param copy_to [in]
 * @param size [in] размер элемента в байтах
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
 * @param pbeg [in] указатель на начало массива
 * @param pend [in] указатель на за последний элемент массива
 * @param size [in] размер элемента в байтах
 */
void move(void *pbeg, void *pend, size_t size)
{
    char buf[size];
    copy_element(pend, buf, size);
    for (char *pcur = (char*)pend; pcur > (char*)pbeg; pcur -= size)
        copy_element(pcur - size, pcur, size);
    copy_element(buf, pbeg, size);
}

/**
 Определяет позицию вставки элемента в уже отсортированной части массива.
 * @param beg [in] указатель на начало массива
 * @param end [in] указатель на за последний элемент отсортированной части массива
 * @param n [in] размер элемента в байтах
 * @return Указатель на позицию вставки.
 */
char *find_place(char *beg, char *end, size_t n, int (*cmp)(const void*, const void*))
{
    for (char *pj = beg; pj < end; pj += n)
        if (cmp(pj, end) > 0)
            return pj;
    return end;
}

/**
 Сортирует массив по возрастанию методом "вставок".
 * @param base [in] указатель на начало массива
 * @param nmemb [in] количество элементов
 * @param n [in] размер элемента в байтах
 */
void mysort(void *base, size_t nmemb, size_t n, int (*cmp)(const void*, const void*))
{
    char *beg = base;
    char *pend = beg + nmemb * n;
    char *place;
    for (char *pi = beg + n; pi < pend; pi += n)
    {
        place = find_place(beg, pi, n, cmp);
        move(place, pi, n);
    }
}

/**
 Сравнивает два целых числа.
 * @param l [in] указатель на 1 число
 * @param r [in] указатель на 2 число
 * @return Возвращает отрицательное число, если правое число больше левого; 0, если числа равны; положительное число, если левое число больше правого.
 */
int cmp_int(const void *l, const void *r)
{
    return (*(int*)l) - (*(int*)r);
}

/**
 Сравнивает два символа.
 * @param l [in] указатель на 1 символ
 * @param r [in] указатель на 2 символ
 * @return Возвращает отрицательное число, если правое число больше левого; 0, если числа равны; положительное число, если левое число больше правого.
 */
int cmp_char(const void *l, const void *r)
{
    return (*(char*)l) - (*(char*)r);
}

/**
 Сравнивает два действительных числа.
 * @param l [in] указатель на 1 число
 * @param r [in] указатель на 2 число
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

/**
 Сортирует массив, сохраняет результат в файл и выводит результат на экран.
 * @param f [in] файловая переменная
 * @param pbeg [in] указатель на начало массива
 * @param pend [in] указатель на за последний элемент массива
 */
void solve(FILE *f, int *pbeg, int *pend)
{
    mysort(pbeg, pend - pbeg, sizeof(int), cmp_int);
    save(f, pbeg, pend);
    printf("Result ");
    print(pbeg, pend);
}
