#ifndef IN_OUT_H
#define IN_OUT_H

#include <stdio.h>

int count_n(FILE *f);
int read_array(FILE *f, int *pbeg, int *pend);
int read(FILE *f, int **pbeg, int **pend);
int save(FILE *f, const int *pbeg, const int *pend);
void print(const int *pbeg, const int *pend);

#endif // IN_OUT_H
