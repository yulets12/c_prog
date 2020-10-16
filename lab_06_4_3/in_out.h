#ifndef IN_OUT_H
#define IN_OUT_H

#include <stdio.h>
#define OK 0
#define ERR_WRONG_CMD 1
#define ERR_FILE 2
#define ERR_RANGE 3
#define N 100

int input(FILE *f, int *pbeg, int **pend);
void print(const int *pbeg, const int *pend);

#endif //IN_OUT_H
