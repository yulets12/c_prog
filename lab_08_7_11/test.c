#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "in_out.h"
#include "operations.h"
#include "errors.h"
#define EPS 0.000001
#define N 10
#define M 10

int matrix_cmp(double **matrix1, double matrix2[N][M], int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (fabs(matrix1[i][j] - matrix2[i][j]) > EPS)
                return 0;
    return 1;
}

void test_read_matrix(void)
{
    int err_cnt = 0;
    //empty file
    {
        double **matrix = NULL;
        int n, m;
        if (read_matrix("tests/empty.txt", &matrix, &n, &m) != ERR_IO)
            err_cnt++;
    }
    //file don't exist
    {
        double **matrix = NULL;
        int n, m;
        if (read_matrix("tests/errfile.txt", &matrix, &n, &m) != ERR_FILE)
            err_cnt++;
    }
    //n = 0
    {
        double **matrix = NULL;
        int n, m;
        if (read_matrix("tests/row.txt", &matrix, &n, &m) != ERR_EMPTY)
            err_cnt++;
    }
    //m = 0
    {
        double **matrix = NULL;
        int n, m;
        if (read_matrix("tests/column.txt", &matrix, &n, &m) != ERR_EMPTY)
            err_cnt++;
    }
    //correct
    {
        double **matrix1 = NULL;
        int n, m;
        double matrix2[N][M] = { { 0.5, -1.5, 2.5 }, { 7.5, -4.5, 1.5 } };
        if (read_matrix("tests/mtr1_2.txt", &matrix1, &n, &m) != OK)
            err_cnt++;
        else
        {
            if (matrix_cmp(matrix1, matrix2, n, m) != 1)
                err_cnt++;
        }
        free_matrix(matrix1, n);
    }
    printf("READ_MATRIX(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_addition(void)
{
    int err_cnt = 0;
    {
        double **matrix1 = NULL, **matrix2 = NULL, **res1 = NULL;
        int n, m;
        double res2[N][M] = { { 2, 4, 6 }, { 8, 10, 12 }, { 14, 16, 18 } };
        assert(read_matrix("tests/mtr1_1.txt", &matrix1, &n, &m) == OK);
        assert(read_matrix("tests/mtr2_1.txt", &matrix2, &n, &m) == OK);
        res1 = addition(matrix1, matrix2, n, m);
        assert(res1 != NULL);
        if (matrix_cmp(res1, res2, n, m) != 1)
            err_cnt++;
        free_matrix(matrix1, n);
        free_matrix(matrix2, n);
        free_matrix(res1, n);
    }
    {
        double **matrix1 = NULL, **matrix2 = NULL, **res1 = NULL;
        int n, m;
        double res2[N][M] = { { 0, -0.5, 3 }, { 11, 1, 9 } };
        assert(read_matrix("tests/mtr1_2.txt", &matrix1, &n, &m) == OK);
        assert(read_matrix("tests/mtr2_2.txt", &matrix2, &n, &m) == OK);
        res1 = addition(matrix1, matrix2, n, m);
        assert(res1 != NULL);
        if (matrix_cmp(res1, res2, n, m) != 1)
            err_cnt++;
        free_matrix(matrix1, n);
        free_matrix(matrix2, n);
        free_matrix(res1, n);
    }
    printf("ADDITION(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_multiplication(void)
{
    int err_cnt = 0;
    {
        double **matrix1 = NULL, **matrix2 = NULL, **res1 = NULL;
        int n, m, l, n_res = 3, m_res = 2;
        double res2[N][M] = { { 196.7673, 17.7247 }, { 40.425, -19.8773 }, { 19.03, -17.95 } };
        assert(read_matrix("tests/mtr1_3.txt", &matrix1, &n, &m) == OK);
        assert(read_matrix("tests/mtr2_3.txt", &matrix2, &m, &l) == OK);
        res1 = multiplication(matrix1, matrix2, n, m, l);
        assert(res1 != NULL);
        if (n != n_res || l != m_res || matrix_cmp(res1, res2, n, l) != 1)
            err_cnt++;
        free_matrix(matrix1, n);
        free_matrix(matrix2, m);
        free_matrix(res1, n_res);
    }
    {
        double **matrix1 = NULL, **matrix2 = NULL, **res1 = NULL;
        int n, m, l, n_res = 5, m_res = 3;
        double res2[N][M] = { { 2, 4, 6 }, { 7, 4, 1 }, { 3, 8, 9 }, { 5, 1, 3 }, { 9, 0, 5 } };
        assert(read_matrix("tests/mtr1_5.txt", &matrix1, &n, &m) == OK);
        assert(read_matrix("tests/mtr2_5.txt", &matrix2, &m, &l) == OK);
        res1 = multiplication(matrix1, matrix2, n, m, l);
        assert(res1 != NULL);
        if (n != n_res || l != m_res || matrix_cmp(res1, res2, n, l) != 1)
            err_cnt++;
        free_matrix(matrix1, n);
        free_matrix(matrix2, m);
        free_matrix(res1, n_res);
    }
    printf("MULTIPLICATION(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_determinant(void)
{
    int err_cnt = 0;
    {
        double **matrix = NULL;
        double det = 0, resdet = 0;
        int n, m;
        assert(read_matrix("tests/mtr1_1.txt", &matrix, &n, &m) == OK);
        if (determinant(matrix, n, &det) != OK)
            err_cnt++;
        else
        {
            if (fabs(det - resdet) > EPS)
                err_cnt++;
        }
        free_matrix(matrix, n);
    }
    {
        double **matrix = NULL;
        double det = 0, resdet = -3;
        int n, m;
        assert(read_matrix("tests/mtr2_4.txt", &matrix, &n, &m) == OK);
        if (determinant(matrix, n, &det) != OK)
            err_cnt++;
        else
        {
            if (fabs(det - resdet) > EPS)
                err_cnt++;
        }
        free_matrix(matrix, n);
    }
    {
        double **matrix = NULL;
        double det = 0, resdet = 4;
        int n, m;
        assert(read_matrix("tests/det1.txt", &matrix, &n, &m) == OK);
        if (determinant(matrix, n, &det) != OK)
            err_cnt++;
        else
        {
            if (fabs(det - resdet) > EPS)
                err_cnt++;
        }
        free_matrix(matrix, n);
    }
    {
        double **matrix = NULL;
        double det = 0, resdet = 909455;
        int n, m;
        assert(read_matrix("tests/det2.txt", &matrix, &n, &m) == OK);
        if (determinant(matrix, n, &det) != OK)
            err_cnt++;
        else
        {
            if (fabs(det - resdet) > EPS)
                err_cnt++;
        }
        free_matrix(matrix, n);
    }
    printf("DETERMINANT(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_make_new_matrix(void)
{
    int err_cnt = 0;
    {
        double **matrix = NULL, **new_matrix = NULL;
        int n, m, n_res = 3;
        double res[N][M] = { { 12, 3, -9 }, { 34, -6, 14 }, { 55, -89, 1 } };
        assert(read_matrix("tests/det2.txt", &matrix, &n, &m) == OK);
        new_matrix = allocate_matrix(n - 1, n - 1);
        assert(new_matrix != NULL);
        make_new_matrix(matrix, new_matrix, n, 1, 2);
        assert(new_matrix != NULL);
        if (matrix_cmp(new_matrix, res, n_res, n_res) != 1)
            err_cnt++;
        free_matrix(matrix, n);
        free_matrix(new_matrix, n_res);
    }
    {
        double **matrix = NULL, **new_matrix = NULL;
        int n, m, n_res = 2;
        double res[N][M] = { { 5, 6 }, { 8, 9 } };
        assert(read_matrix("tests/mtr1_1.txt", &matrix, &n, &m) == OK);
        new_matrix = allocate_matrix(n - 1, n - 1);
        assert(new_matrix != NULL);
        make_new_matrix(matrix, new_matrix, n, 0, 0);
        assert(new_matrix != NULL);
        if (matrix_cmp(new_matrix, res, n_res, n_res) != 1)
            err_cnt++;
        free_matrix(matrix, n);
        free_matrix(new_matrix, n_res);
    }
    printf("MAKE_NEW_MATRIX(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_inverse(void)
{
    int err_cnt = 0;
    {
        double **matrix = NULL, **inv_matrix = NULL;
        int n, m;
        assert(read_matrix("tests/mtr1_1.txt", &matrix, &n, &m) == OK);
        if (inverse(matrix, &inv_matrix, n) != DET)
            err_cnt++;
        free_matrix(matrix, n);
    }
    {
        double **matrix = NULL, **inv_matrix = NULL;
        int n, m, n_res = 2;
        double res[N][M] = { { -0.333333, 0.666667 }, { 0.666667, -0.333333 } };
        assert(read_matrix("tests/mtr2_4.txt", &matrix, &n, &m) == OK);
        if (inverse(matrix, &inv_matrix, n) != OK)
            err_cnt++;
        else
        {
            assert(inv_matrix != NULL);
            if (matrix_cmp(inv_matrix, res, n_res, n_res) != 1)
                err_cnt++;
        }
        free_matrix(matrix, n);
        free_matrix(inv_matrix, n_res);
    }
    {
        double **matrix = NULL, **inv_matrix = NULL;
        int n, m, n_res = 3;
        double res[N][M] = { { 0.2, -0.28, 0.08 }, { -0.066667, 0.115556, 0.062222 }, { 0.066667, 0.017778, -0.028889 } };
        assert(read_matrix("tests/inv1.txt", &matrix, &n, &m) == OK);
        if (inverse(matrix, &inv_matrix, n) != OK)
            err_cnt++;
        else
        {
            assert(inv_matrix != NULL);
            if (matrix_cmp(inv_matrix, res, n_res, n_res) != 1)
                err_cnt++;
        }
        free_matrix(matrix, n);
        free_matrix(inv_matrix, n_res);
    }
    printf("INVERSE(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_edit_row(void)
{
    int err_cnt = 0;
    {
        double **matrix = NULL, **inv_matrix = NULL;
        int n, m, n_res = 3, m_res = 3;
        double res[N][M] = { { 1, 2, 3 }, { 0.8, 1, 1.2 }, { 7, 8, 9 } };
        assert(read_matrix("tests/mtr1_1.txt", &matrix, &n, &m) == OK);
        inv_matrix = allocate_matrix(n, n);
        assert(inv_matrix != NULL);
        make_e_matrix(inv_matrix, n);
        edit_row(matrix, inv_matrix, n, 1, 1);
        assert(inv_matrix != NULL);
        if (matrix_cmp(matrix, res, n_res, m_res) != 1)
            err_cnt++;
        free_matrix(matrix, n);
        free_matrix(inv_matrix, n_res);
    }
    {
        double **matrix = NULL, **inv_matrix = NULL;
        int n, m, n_res = 3, m_res = 3;
        double res[N][M] = { { 1, 2, 3 }, { 4, 5, 6 }, { 1, 1.142857, 1.285714 } };
        assert(read_matrix("tests/mtr1_1.txt", &matrix, &n, &m) == OK);
        inv_matrix = allocate_matrix(n, n);
        assert(inv_matrix != NULL);
        make_e_matrix(inv_matrix, n);
        edit_row(matrix, inv_matrix, n, 2, 0);
        assert(inv_matrix != NULL);
        if (matrix_cmp(matrix, res, n_res, m_res) != 1)
            err_cnt++;
        free_matrix(matrix, n);
        free_matrix(inv_matrix, n_res);
    }
    printf("EDIT_ROW(): %s\n", err_cnt ? "FAILED" : "OK");
}

void test_minus_row(void)
{
    int err_cnt = 0;
    {
        double **matrix = NULL, **inv_matrix = NULL;
        int n, m, n_res = 3, m_res = 3;
        double res[N][M] = { { 1, 2, 3 } , { 1.5, 0, -1.5 }, { 7, 8, 9 } };
        assert(read_matrix("tests/mtr1_1.txt", &matrix, &n, &m) == OK);
        inv_matrix = allocate_matrix(n, n);
        assert(inv_matrix != NULL);
        make_e_matrix(inv_matrix, n);
        minus_row(matrix, inv_matrix, n, 0, 1, 2.5);
        assert(inv_matrix != NULL);
        if (matrix_cmp(matrix, res, n_res, m_res) != 1)
            err_cnt++;
        free_matrix(matrix, n);
        free_matrix(inv_matrix, n_res);
    }
    {
        double **matrix = NULL, **inv_matrix = NULL;
        int n, m, n_res = 3, m_res = 3;
        double res[N][M] = { { 1, 2, 3 }, { 4, 5, 6 }, { 0, -6, -12 } };
        assert(read_matrix("tests/mtr1_1.txt", &matrix, &n, &m) == OK);
        inv_matrix = allocate_matrix(n, n);
        assert(inv_matrix != NULL);
        make_e_matrix(inv_matrix, n);
        minus_row(matrix, inv_matrix, n, 0, 2, 7);
        assert(inv_matrix != NULL);
        if (matrix_cmp(matrix, res, n_res, m_res) != 1)
            err_cnt++;
        free_matrix(matrix, n);
        free_matrix(inv_matrix, n_res);
    }
    printf("MINUS_ROW(): %s\n", err_cnt ? "FAILED" : "OK");
}

int main(void)
{
    test_addition();
    test_determinant();
    test_edit_row();
    test_inverse();
    test_make_new_matrix();
    test_minus_row();
    test_multiplication();
    test_read_matrix();

    return 0;
}
