#ifndef IN_OUT_H
#define IN_OUT_H

#include <stdio.h>
#define MAX_LENGTH 100

int read_matrix(FILE *f, double **matrix, int *n, int *m);
char*split(char *str);
void print_matrix(double *matrix, int n, int m);

#endif // IN_OUT_H
