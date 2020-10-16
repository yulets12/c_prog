#ifndef OPERATIONS_H
#define OPERATIONS_H

double**addition(double **matrix1, double **matrix2, int n, int m);
double**multiplication(double **matrix1, double **matrix2, int n, int m, int l);
void make_new_matrix(double **matrix, double **new_matrix, int n, int id, int jd);
int determinant(double **matrix, int n, double *det);
void make_e_matrix(double **matrix, int n);
int inverse(double **matrix, double ***inv_matrix, int n);
void edit_row(double **matrix, double **inv_matrix, int n, int i, int j);
void minus_row(double **matrix, double **inv_matrix, int n, int i1, int i2, double d);
void minus_high_rows(double **matrix, double **inv_matrix, int n, int i);
void minus_low_rows(double **matrix, double **inv_matrix, int n, int i);
void swap_rows(double **matrix, double **inv_matrix, int i1, int i2, int n);
int find_max_element(double **matrix, int icur, int n);
void choose_main_element(double **matrix, double **inv_matrix, int icur, int n);

#endif // OPERATIONS_H
