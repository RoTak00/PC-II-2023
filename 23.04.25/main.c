#include <stdio.h>
#include <stdlib.h>

int min(int a, int b)
{
    return a > b ? b : a;
}
int main()
{
    int n;
    scanf("%d", &n);

    int *v = calloc(n + 3, sizeof(int));
    int n2 = 0, n3 = 0, n5 = 0;
    v[0] = 1;
    int it = 1;
    while (it <= n)
    {

        int next = min(2 * v[n2], min(3 * v[n3], 5 * v[n5]));
        v[it++] = next;

        printf("%d ", next);
        if (next == 2 * v[n2])
            n2 += 1;
        if (next == 3 * v[n3])
            n3 += 1;
        if (next == 5 * v[n5])
            n5 += 1;
    }
}