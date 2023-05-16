/** 
 * perechile de elemente consecutive din sir 
 * cu proprietatea ca cmmdc al elementelor
 * este egal cu valoarea d
 **/
#include <stdio.h>
#include <stdlib.h>

int nrcifdist(int n)
{
    unsigned int res = 0;
    do
    {
        char k = n % 10;
        res |= (1 << k);
        n /= 10;

    } while (n);

    int cnt = 0;
    while(res)
    {
        if(res % 2) cnt++;
        res /= 2;
    }
    return cnt;
    
}

void fun(int *cmax)
{
    int n;
    scanf("%d", &n);
    if(n == 0) return;


    int nr_cif = nrcifdist(n);
    if(nr_cif > *cmax)
        *cmax = nr_cif;
    fun(cmax);

    if(nr_cif == *cmax)
        printf("%d ", n);

}


int main()
{
    
    int x;
    fun(&x);
    printf("\n%d cifre distincte\n", x);
   

}