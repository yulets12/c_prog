#ifndef IN_OUT_H
#define IN_OUT_H

#include <stdio.h>

void print_inf(void);
double**allocate_matrix(int n, int m);
int read_matrix(const char *fname, double ***matrix, int *n, int *m);
void print_matrix(FILE *f, double **matrix, int n, int m);
int print_matrix_to_file(const char *fname, double **matrix, int n, int m);
void free_matrix(double **matrix, int n);

#endif // IN_OUT_H
