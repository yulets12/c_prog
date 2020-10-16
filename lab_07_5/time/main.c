#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"sort.h"
#define N 20

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d) );
    return d;
}

void make_rand_arr(int *a, int n)
{
    for (int i = 0; i < n; i++)
        a[i] = rand();
}

void make_sorted_arr(int *a, int n)
{
    for (int i = 0; i < n; i++)
        a[i] = i;
}

void make_reverse_arr(int *a, int n)
{
    for (int i = 0; i < n; i++)
        a[i] = n - i;
}

void copy_array(int *a, int *b, int n)
{
    for (int i = 0; i < n; i++)
        b[i] = a[i];
}

unsigned long long check_time_my(int *a, int n)
{
    unsigned long long te, tb;
    tb = tick();
    mysort(a, n, sizeof(int), cmp_int);
    te = tick();
    return te - tb;
}

unsigned long long check_time_q(int *a, int n)
{
    unsigned long long te, tb;
    tb = tick();
    qsort(a, n, sizeof(int), cmp_int);
    te = tick();
    return te - tb;
}

int main(void)
{
    unsigned long long msum, qsum;
    unsigned long t;
    int beg, end, step, k = 0;
    FILE *fmr, *fqr, *fms, *fqs, *fma, *fqa, *f;

    printf("begin, end, step: ");
    scanf("%d%d%d", &beg, &end, &step);

    srand(time(NULL));
    fmr = fopen("my_rand.txt", "w");
    fqr = fopen("q_rand.txt", "w");
    fms = fopen("my_sort.txt", "w");
    fqs = fopen("q_sort.txt", "w");
    fma = fopen("my_rev.txt", "w");
    fqa = fopen("q_rev.txt", "w");
    f = fopen("n.txt", "w");
    for (int n = beg; n <= end; n += step)
    {
        k++;
        int a[n];
        int b[n];
        msum = 0;
        qsum = 0;
        make_rand_arr(a, n);
        for (int i = 0; i < N; i++)
        {
            copy_array(a, b, n);
            msum += check_time_my(b, n);
            copy_array(a, b, n);
            qsum += check_time_q(b, n);
        }

        t = msum / N;
        fprintf(fmr, "%lu\n", t);
        t = qsum / N;
        fprintf(fqr, "%lu\n", t);
//        
        msum = 0;
        qsum = 0;
        make_sorted_arr(a, n);
        for (int i = 0; i < N; i++)
        {
            copy_array(a, b, n);
            msum += check_time_my(b, n);
            copy_array(a, b, n);
            qsum += check_time_q(b, n);
        }
        t = msum / N;
        fprintf(fms, "%lu\n", t);
        t = qsum / N;
        fprintf(fqs, "%lu\n", t);
//
        msum = 0;
        qsum = 0;
        make_reverse_arr(a, n);
        for (int i = 0; i < N; i++)
        {
            copy_array(a, b, n);
            msum += check_time_my(b, n);
            copy_array(a, b, n);
            qsum += check_time_q(b, n);
        }
        t = msum / N;
        fprintf(fma, "%lu\n", t);
        t = qsum / N;
        fprintf(fqa, "%lu\n", t);

        fprintf(f, "%d\n", n);
    }
    printf("%d",k);
    fclose(fmr);
    fclose(fqr);
    fclose(fms);
    fclose(fqs);
    fclose(fma);
    fclose(fqa);
    fclose(f);
    return 0;
}
