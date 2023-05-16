#include <stdlib.h>
#include <stdio.h>

float summation(float * v, int left, int right, int m)
{
    if(right - left < m)
    {
        float s = 0;
        for(int i = left; i < right; ++i)
            s += v[i];
        return s;
    }

    int mid = (right + left) / 2;
    return summation(v, left, mid, m) + summation(v, mid, right, m);
}

int main()
{
    FILE * fin, * fout;
    fin = fopen("sum.in", "r");
    if(fin == NULL)
    {
        perror("fopen sum.in");
        exit(1);
    }

    int n; float *v;
    fscanf(fin, "%d", &n);

    v = (float*)malloc(sizeof(float) * n);
    if(v == NULL)
    {
        perror("malloc v");
        fclose(fin);
        exit(1);
    }

    for(int i = 0; i < n; ++i)
        fscanf(fin, "%f", v + i);

    fclose(fin);

    /*for(int i = 1; i <= n; ++i)
        printf("%f\n", v[i]);*/

    fout = fopen("sum.out", "w");
    if(fout == NULL)
    {
        perror("fopen sum.out");
        free(v);
            exit(1);
    }
    for(int i = 2; i <= n; ++i)
    {
        fprintf(fout, "%d: %f\n", i, summation(v, 0, n, i));
    }

}