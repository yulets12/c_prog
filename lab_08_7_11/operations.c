#include <stdio.h>
#include "operations.h"
#include "in_out.h"
#include "errors.h"

/**
 * Выполняет сложение матриц matrix1 и matrix2 размера n x m.
 * @param matrix1 [in]
 * @param matrix2 [in]
 * @param n [in]
 * @param m [in]
 * @return Возвращает матрицу, представляющую собой сумму исходных матриц.
 */
double**addition(double **matrix1, double **matrix2, int n, int m)
{
    double **buf;
    buf = allocate_matrix(n, m);
    if (!buf)
        return NULL;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            buf[i][j] = matrix1[i][j] + matrix2[i][j];
    return buf;
}

/**
 * Выполняет умножение матрицы matrix1 размера n x m на матрицу matrix2 размера m x l.
 * @param matrix1 [in]
 * @param matrix2 [in]
 * @param n [in]
 * @param m [in]
 * @param l [in]
 * @return Возвращает матрицу, представляющую собой произведение исходных матриц.
 */
double**multiplication(double **matrix1, double **matrix2, int n, int m, int l)
{
    double **buf;
    buf = allocate_matrix(n, l);
    if (!buf)
        return NULL;
    double sum;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < l; j++)
        {
            sum = 0;
            for (int k = 0; k < m; k++)
                sum += matrix1[i][k] * matrix2[k][j];
            buf[i][j] = sum;
        }
    return buf;
}

/**
 * Создает матрицу new_matrix, определитель которой является дополнитильным минором матрицы matrix размера n x n при вычеркивании id строки и jd столбца.
 * @param matrix [in]
 * @param new_matrix [out]
 * @param n [in]
 * @param id [in]
 * @param jd [in]
 */
void make_new_matrix(double **matrix, double **new_matrix, int n, int id, int jd)
{
    int in = 0, jn = 0;
    for (int i = 0; i < n; i++)
        if (i != id)
        {
            jn = 0;
            for (int j = 0; j < n; j++)
                if (j != jd)
                {
                    new_matrix[in][jn] = matrix[i][j];
                    jn++;
                }
            in++;
        }
}

/**
 * Вычисляет определитель det матрицы matrix размера n x n.
 * @param matrix [in]
 * @param n [in]
 * @param det [out]
 * @return Возвращает OK, если ошибок не было; возвращает ERR_MEM, если произошла ошибка при выделении памяти.
 */
int determinant(double **matrix, int n, double *det)
{
    if (n == 1)
    {
        *det = matrix[0][0];
        return OK;
    }

    if (n == 2)
    {
        *det = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
        return OK;
    }

    int new_n = n - 1;
    double **new_matrix = allocate_matrix(new_n, new_n);
    double new_det;
    if (!new_matrix)
        return ERR_MEM;

    int sgn = 1;
    for (int i = 0; i < n; i++)
    {
        new_det = 0;
        make_new_matrix(matrix, new_matrix, n, i, 0);
        if (determinant(new_matrix, new_n, &new_det) == OK)
        {
            *det += sgn * matrix[i][0] * new_det;
            sgn *= -1;
        }
        else
        {
            free_matrix(new_matrix, new_n);
            return ERR_MEM;
        }
    }
    free_matrix(new_matrix, new_n);
    return OK;
}

/**
 * Создает единичную матрицу matrix размера n x n.
 * @param matrix [out]
 * @param n [in]
 */
void make_e_matrix(double **matrix, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                matrix[i][j] = 1;
            else
                matrix[i][j] = 0;
        }
}

/**
 * Преобразует строку матриц matrix и inv_matrix размера n x n так, чтобы элемент matrix[i][j] = 1.
 * @param matrix [out]
 * @param inv_matrix [out]
 * @param n [in]
 * @param i [in]
 * @param j [in]
 */
void edit_row(double **matrix, double **inv_matrix, int n, int i, int j)
{
    double d = matrix[i][j];

    for (int j0 = 0; j0 < n; j0++)
    {
        matrix[i][j0] /= d;
        inv_matrix[i][j0] /= d;
    }
    matrix[i][j] = 1;
}

/**
 * В матрицах matrix и inv_matrix размера n x n вычитает из строки i2 строку i1, умноженную на d.
 * @param matrix [out]
 * @param inv_matrix [out]
 * @param n [in]
 * @param i1 [in]
 * @param i2 [in]
 * @param d [in]
 */
void minus_row(double **matrix, double **inv_matrix, int n, int i1, int i2, double d)
{
    for (int j = 0; j < n; j++)
    {
        matrix[i2][j] -= (matrix[i1][j] * d);
        inv_matrix[i2][j] -= (inv_matrix[i1][j] * d);
    }
}

/**
 * Вычитает из строки i матриц matrix и inv_matrix размера n x n все строки, которые располагаются выше i-ой.(в результате применения ко всем строкам получается верхняя треугольная матрица)
 * @param matrix [out]
 * @param inv_matrix [out]
 * @param n [in]
 * @param i [in]
 */
void minus_high_rows(double **matrix, double **inv_matrix, int n, int i)
{
    for (int j = 0; j < i; j++)
    {
        double d = matrix[i][j];
        minus_row(matrix, inv_matrix, n, j, i, d);
    }
}

/**
 * Вычитает из строки i матриц matrix и inv_matrix размера n x n все строки, которые располагаются ниже i-ой.(в результате применения ко всем строкам получается нижняя треугольная матрица)
 * @param matrix [out]
 * @param inv_matrix [out]
 * @param n [in]
 * @param i [in]
 */
void minus_low_rows(double **matrix, double **inv_matrix, int n, int i)
{
    for (int j = n - 1; j > i; j--)
    {
        double d = matrix[i][j];
        minus_row(matrix, inv_matrix, n, j, i, d);
    }
}

/**
 * Вычисляет матрицу inv_matrix, которая является обратной для матрицы matrix размера n x n.
 * @param matrix [in]
 * @param inv_matrix [out]
 * @param n [in]
 * @return Возвращает OK, если ошибок не было; возвращает ERR_MEM, если произошла ошибка при выделении памяти; возвращает DET, если определитель исходной матрицы равен 0.
 */
int inverse(double **matrix, double ***inv_matrix, int n)
{
    double det = 0;

    if (determinant(matrix, n, &det) != OK)
        return ERR_MEM;
    if (det == 0)
        return DET;
    (*inv_matrix) = allocate_matrix(n, n);
    if (!(*inv_matrix))
        return ERR_MEM;
    make_e_matrix(*inv_matrix, n);
    choose_main_element(matrix, *inv_matrix, 0, n);
    edit_row(matrix, *inv_matrix, n, 0, 0);
    for (int i = 1; i < n; i++)
    {
        minus_high_rows(matrix, *inv_matrix, n, i);
        choose_main_element(matrix, *inv_matrix, i, n);
        edit_row(matrix, *inv_matrix, n, i, i);
    }
    edit_row(matrix, *inv_matrix, n, n - 1, n - 1);
    for (int i = n - 1; i >= 0; i--)
        minus_low_rows(matrix, *inv_matrix, n, i);
    return OK;
}

/**
 * Меняет местами строки i1 и i2 матрицы matrix.
 * @param matrix [out]
 * @param i1 [in]
 * @param i2 [in]
 */
void swap_rows(double **matrix, double **inv_matrix, int i1, int i2, int n)
{
//    double tmp;
//    for (int j = 0; j < n; j++)
//    {
//        tmp = matrix[i1][j];
//        matrix[i1][j] = matrix[i2][j];
//        matrix[i2][j] = tmp;
//        tmp = inv_matrix[i1][j];
//        inv_matrix[i1][j] = inv_matrix[i2][j];
//        inv_matrix[i2][j] = tmp;
//    }
    (void) n;
    double *tmp;
    tmp = matrix[i1];
    matrix[i1] = matrix[i2];
    matrix[i2] = tmp;
    tmp = inv_matrix[i1];
    inv_matrix[i1] = inv_matrix[i2];
    inv_matrix[i2] = tmp;
}

/**
 * Функция для выбора главного элемента при преобразованиях матрицы.
 * @param matrix [out]
 * @param icur [in]
 * @param n [in]
 */
void choose_main_element(double **matrix, double **inv_matrix, int icur, int n)
{
    int imax = find_max_element(matrix, icur, n);
    swap_rows(matrix, inv_matrix, icur, imax, n);
}

/**
 * Находит номер строки с максимальным элементом столбца icur.
 * @param matrix [in]
 * @param icur [in]
 * @param n [in]
 * @return Возвращает номер строки с максимальным элементом столбца icur.
 */
int find_max_element(double **matrix, int icur, int n)
{
    int imax = icur;
    for (int i = icur + 1; i < n; i++)
        if (matrix[i][icur] > matrix[imax][icur])
            imax = i;
    return imax;
}
