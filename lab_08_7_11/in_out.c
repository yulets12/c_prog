#include <string.h>
#include <stdlib.h>
#include "in_out.h"
#include "errors.h"

/**
 * Выводит справочную информацию на экран.
 */
void print_inf(void)
{
    printf("Command line format:\n");
    printf("app.exe action mtr_1.txt [mtr_2.txt] res.txt\n");
    printf("Actions:\n");
    printf("        a - adding\n");
    printf("        m - multiplication\n");
    printf("        o - calculation of the inverse matrix by the method of elementary transformations\n");
    printf("        h - help\n");
}

/**
 * Создает матрицу, состоящую из n строк и m столбцов.
 * @param n [in]
 * @param m [in]
 * @return Возвращает матрицу или NULL - в случает ошибки при выделении памяти.
 */
double**allocate_matrix(int n, int m)
{
//    double **ptrs, *data;
//    ptrs = malloc((n + 1) * sizeof(double*));
//    if (!ptrs)
//        return NULL;
//    data = malloc(n * m * sizeof(double));
//    if (!data)
//    {
//        free(ptrs, n);
//        return NULL;
//    }
//    for (int i = 0; i < n; i++)
//        ptrs[i] = data + i * m;
//    ptrs[n] = data;

//    return ptrs;

    double **ptrs, *data;
    ptrs = malloc(n * sizeof(double*));
    if (!ptrs)
        return NULL;
    for (int i = 0; i < n; i++)
    {
        data = malloc(m * sizeof(double));
        if (!data)
        {
            free_matrix(ptrs, n);
            return NULL;
        }
        else
            ptrs[i] = data;
    }
    return ptrs;
}

/**
 * Считывает матрицу из файла с именем fname.
 * @param fname [in]
 * @param matrix [out] считанная матрица
 * @param n [out] количество строк
 * @param m [out] количество столбцов
 * @return Возвращает ОК при успешном считывании, ERR_MEM - при ошибке при выделении памяти, ERR_IO - в случает неверного ввода.
 */
int read_matrix(const char *fname, double ***matrix, int *n, int *m)
{
    FILE *f;
    int rc = OK;

    f = fopen(fname, "r");
    if (!f)
        rc = ERR_FILE;
    else
    {
        if (fscanf(f, "%d%d", n, m) == 2)
        {
            if (*m <= 0 || *n <= 0)
                rc = ERR_EMPTY;
            else
            {
                (*matrix) = allocate_matrix(*n, *m);
                if (!(*matrix))
                    rc = ERR_MEM;
                else
                {
                    for (int i = 0; i < *n; i++)
                        for (int j = 0; j < *m; j++)
                            if (fscanf(f, "%lf", (*matrix)[i] + j) != 1)
                            {
                                free_matrix(*matrix, *n);
                                rc = ERR_IO;
                            }
                }
            }
        }
        else
            rc = ERR_IO;
        fclose(f);
    }

    return rc;
}

/**
 Печатает матрицу matrix, у которой n строк и m столбцов, в файл f.
 * @param f  [in]
 * @param matrix  [in]
 * @param n  [in]
 * @param m  [in]
 */
void print_matrix(FILE *f, double **matrix, int n, int m)
{
    fprintf(f, "%d ", n);
    fprintf(f, "%d\n", m);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            fprintf(f, "%lf ", matrix[i][j]);
        fprintf(f, "\n");
    }
}

/**
 Печатает матрицу matrix, у которой n строк и m столбцов, в файл c с именем fanme.
 * @param fname [in]
 * @param matrix [in]
 * @param n [in]
 * @param m [in]
 * @return
 */
int print_matrix_to_file(const char *fname, double **matrix, int n, int m)
{
    FILE *f;
    f = fopen(fname, "w");
    if (!f)
        return ERR_FILE;
    print_matrix(f, matrix, n, m);
    fclose(f);
    return OK;
}

/**
 Освобождает память.
 * @param matrix [in]
 */
void free_matrix(double **matrix, int n)
{
//    free(matrix[n]);
//    free(matrix);
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}
