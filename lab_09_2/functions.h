#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <unistd.h>
#include <stdio.h>
#define N 128
#define STEP 50

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream);
char*str_replace(const char *source, const char *search, const char *replace);
int my_strlen(const char *str);
int cmpr(const char *str1, const char *str2);
int process(FILE *f_in, FILE *f_out, const char *search, const char *replace);
int str_cmpr(const char *str1, const char *str2);
void res_append(char *result, int *reslen, const char *replace, int replace_len);

#endif // FUNCTIONS_H
