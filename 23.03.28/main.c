#include <stdio.h>
#include <stdlib.h>

int divimp(int *v, int st, int fin)
{
    if (fin - st == 1)
        return v[st];

    int mid = st + (fin - st) / 2;

    int l1 = divimp(v, st, mid);
    int l2 = divimp(v, mid, fin);

    return (l1 < l2) ? l1 : l2;
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