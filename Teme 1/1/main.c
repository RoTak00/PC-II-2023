#include <stdio.h>
#include <stdlib.h>

int searchTop(int * v, int n)
{
    int left = 0, right = n;
    int index;
    while(right - left > 0)
    {
        index = (left + right) / 2;
        if(index == 0 || index == n - 1)
            return -1;
        if(v[index - 1] < v[index] && v[index + 1] < v[index])
            return index;
        
        if(v[index - 1] > v[index])
            right = index;
        if(v[index + 1] > v[index])
            left = index;
    }

    return -1;
}
int main()
{
    FILE* fin , * fout;

    fin = fopen("secventa.in", "r");
    if(fin == NULL)
    {
        perror("fopen secventa.in");
        exit(EXIT_FAILURE);
    }

    int n = 0, *v;
    fscanf(fin, "%d", &n);
    v = (int*)malloc(sizeof(int) * n);
    if(v == NULL)
    {
        perror("malloc v");
        fclose(fin);
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < n; ++i)
        fscanf(fin, "%d", v + i);
    
    fout = fopen("secventa.out", "w");
    if(fout == NULL)
    {
        perror("fopen secventa.out");
        free(v);
        exit(EXIT_FAILURE);
    }
    fprintf(fout, "%d", searchTop(v, n));

    free(v);
    fclose(fin);
    fclose(fout);

    
}