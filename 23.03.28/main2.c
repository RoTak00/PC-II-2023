// cmmdc a n elem naturale nenule folosind div imp

#include <stdio.h>
#include <stdlib.h>

int cmmdc(int a, int b)
{
    if (b == 0)
        return a;
    return cmmdc(b, a % b);
}

int divimp(int *v, int st, int fin)
{
    if (fin - st == 1)
        return v[st];

    int mid = st + (fin - st) / 2;

    int v1 = divimp(v, st, mid);
    int v2 = divimp(v, mid, fin);

    return cmmdc(v1, v2);
}
int main()
{
    int n;
    scanf("%d", &n);

    int *v = (int *)malloc(sizeof(int) * n);
    if (v == NULL)
    {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < n; ++i)
        scanf("%d", v + i);

    printf("%d\n", divimp(v, 0, n));
}