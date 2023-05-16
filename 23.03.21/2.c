/** 
 * perechile de elemente consecutive din sir 
 * cu proprietatea ca cmmdc al elementelor
 * este egal cu valoarea d
 **/
#include <stdio.h>
#include <stdlib.h>

int cmmdc(int a, int b)
{
    if(b == 0) return a;
    return cmmdc(b, a % b);
}

void fun(int * v, int n, int d)
{
    if(n == 0) return;
    fun(v, n - 1, d);
    int res = cmmdc(v[n-1], v[n-2]);
    if(res == d)
        printf("(%d %d) => %d\n", v[n-2], v[n-1], res);

}

int main()
{
    
    int n, d;
    scanf("%d", &n);
    scanf("%d", &d);
    int * v = malloc(sizeof(int) * n);

    for(int i = 0; i < n; ++i)
        scanf("%d", v + i);

    fun(v, n, d);

}