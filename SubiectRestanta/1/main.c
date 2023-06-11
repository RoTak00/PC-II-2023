#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE * fin;
    fin = fopen("in.txt", "r");
    if(!fin)
    {
        perror("Eroare la deschiderea fisierului");
        return 1;
    }

    int n;
    fscanf(fin, "%d", &n);
    int * v = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
        fscanf(fin, "%d", &v[i]);

    fclose(fin);

    int * succ = (int*)malloc(n * sizeof(int));
    succ[n - 1] = -1;
    int * len = (int*)malloc(n * sizeof(int));
    len[n - 1] = 1;

    for(int i = n - 1; i >= 0; --i)
    {
        len[i] = 1;
        succ[i] = -1;
        for(int j = i + 1; j < n; ++j)
        {
            if(v[j] > v[i] && len[i] < len[j] + 1)
            {
                succ[i] = j;
                len[i] = len[j] + 1;
            }
        }
    }

    int pmax = 0;
    for(int i = 0; i < n; ++i)
        if(len[i] > len[pmax])
            pmax = i;

    while(pmax != -1)
    {
        printf("%d ", v[pmax]);
        pmax = succ[pmax];
    }

    return 0;

}