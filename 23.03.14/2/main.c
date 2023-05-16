#include <stdio.h>
#include <stdlib.h>

int maj(int* v, int n)
{
    int cand = -1;
    int cnt = 0;

    for(int i = 0; i < n; ++i)
    {
        if(cnt == 0)
        {
            printf("New cand: %d\n", v[i]);
            cand = v[i];
            cnt = 1;
        }
        else if(v[i] == cand)
            cnt += 1;
        else
            cnt -= 1;
    }

    int rcnt = 0;
    for(int i = 0; i < n; ++i)
        if(v[i] == cand)
            rcnt += 1;

    if(rcnt > n / 2 )
        return cand;
    return -1;
}
int main()
{
    FILE * fin;
    fin = fopen("in.txt", "r");
    if(fin == NULL)
    {
        perror("fopen");
        exit(1);
    }

    int n, *v;
    fscanf(fin, "%d", &n);
    v = (int*)malloc(sizeof(int) * n);

    for(int i = 0; i < n; ++i)
    {
        fscanf(fin, "%d", v + i);
    }

    int t = maj(v, n);
    printf("%d\n", t);
}