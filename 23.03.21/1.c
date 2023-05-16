// Functie rec care sa determine nr elem negative dintr-un sir cu n elemente

#include <stdio.h>
#include <stdlib.h>

int negativeElements(int * v, int n)
{
    if(n == 0)
        return 0;
    return (v[n - 1] < 0) + negativeElements(v, n - 1);
}

int negativeElementsDiv(int * v, int st, int fin)
{

    if(st == fin) return v[st] < 0;

    int mid = st + (fin - st) / 2;
    return negativeElementsDiv(v, st, mid) + negativeElementsDiv(v, mid + 1, fin);
}

int main()
{
    int n;
    scanf("%d", &n);
    int * v = malloc(sizeof(int) * n);

    for(int i = 0; i < n; ++i)
        scanf("%d", v + i);

    printf("%d\n", negativeElements(v, n));
    printf("%d\n", negativeElementsDiv(v, 0, n));
}