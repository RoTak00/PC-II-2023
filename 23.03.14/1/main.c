#include <stdio.h>
#include <stdlib.h>

int ncif(int n)
{
    int c = 0;
    do{
        c++;
        n /= 10;
    }while(n);
    return c;
}

int rmcif(int n, int pos)
{
    int k = 1;
    for(int i = 0; i < pos; ++i)
        k *= 10;

    n = (n / (k * 10)) * k + n % k;
    return n;
}

int verifSorted(int t)
{
    //printf("%d -> ", t);
    int last = t % 10;
    t /= 10;
    while(t)
    {
        //printf(": %d > %d  ", last, t % 10);
        if(last < t % 10) return 0;
        last = t % 10;
        t /= 10;
    }
    return 1;
}

void removeDigit(int n)
{
    int nrd = ncif(n);
    int ok = 0;
    for(int i = 0; i < nrd; ++i)
    {
        int t = rmcif(n, i);
        if(verifSorted(t))
        {
            printf("%d\n", t);
            ok = 1;
        }

    }

    if(ok) return;
    printf("Nu au fost gasite solutii!\n");
    
}
int main()
{
    int n;
    scanf("%d", &n);

    removeDigit(n);
}