// cmmdc a n elem naturale nenule folosind div imp

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int divimp(int *v, int x, int st, int fin)
{
    if (st > fin)
        return -1;

    int mid = st + (fin - st) / 2;

    if (v[mid] == x)
        return mid;

    if (x > v[mid])
        return divimp(v, x, mid + 1, fin);
    return divimp(v, x, st, mid - 1);
}

int iter(int *v, int x, int n)
{
    for (int i = 0; i < n; ++i)
    {
        if (v[i] == x)
            return i;
        if (v[i] > x)
            return -1;
    }
}
int main()
{
    int n, x;
    scanf("%d", &n);
    scanf("%d", &x);

    int *v = (int *)malloc(sizeof(int) * n);
    if (v == NULL)
    {
        perror("malloc");
        return 1;
    }
    /*FILE *f = fopen("p", "r");

    for (int i = 0; i < n; ++i)
        fscanf(f, "%d", v + i);
    */

    for (int i = 0; i < n; ++i)
        scanf("%d", v + i);
    clock_t start1 = clock();
    printf("%d\n", divimp(v, x, 0, n));

    double elapsed1 = (double)(clock() - start1) / CLOCKS_PER_SEC;
    printf("time : %f\n", elapsed1);

    clock_t start2 = clock();
    printf("%d\n", iter(v, x, n));
    double elapsed2 = (double)(clock() - start2) / CLOCKS_PER_SEC;
    printf("time : %f\n", elapsed2);
}