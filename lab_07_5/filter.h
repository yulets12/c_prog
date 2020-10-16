#ifndef FILTER_H
#define FILTER_H

int sum_of_elements(const int *pbeg, const int *pend);
int count_elements(const int *pbeg, const int *pend, int sum);
int copy_elements(const int *pabeg, const int *paend, int *pbbeg, int *pbend, int sum);
int key(const int *pabeg, const int *paend, int **pbbeg, int **pbend);

#endif // FILTER_H
