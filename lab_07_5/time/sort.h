#ifndef SORT_H
#define SORT_H

#define NEGATIVE -1
#define POSITIVE 1
#define ZERO 0

void mysort(void *base, size_t nmemb, size_t n, int (*cmp)(const void*, const void*));
void copy_element(void *copy_from, void *copy_to, size_t size);
int cmp_double(const void *l, const void *r);
int cmp_int(const void *l, const void *r);
int cmp_char(const void *l, const void *r);

#endif // SORT_H
