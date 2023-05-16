#include <stdio.h>
#include <stdlib.h>

int count(int* v, int dim, int val)
{
    int cnt = 0;

    for (int i = 0; i < dim; i++)
        if (v[i] <= val)
            cnt++;
 
    return cnt;
}

int kthSmallest(int* v, int dim, int k)
{
    int low = 2000000000;
    int high = 0;

    for (int i = 0; i < dim; i++) {
        if(v[i] < low) low = v[i];
        if(v[i] > high) high = v[i];
    }

    while(low < high)
    {
        int mid = low + (high - low) / 2;

        if (count(v, dim, mid) < k)
            low = mid + 1;
        else
            high = mid;
    }

    return low;
}
int main()
{
    FILE * fin = fopen("Date.in", "r");
    if(fin == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int n, k;
    int * v;

    fscanf(fin, "%d", &n);
    fscanf(fin, "%d", &k);

    v = (int*)malloc(sizeof(int) * n);
    if(v == NULL)
    {
        perror("malloc v");
        fclose(fin);
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < n; ++i)
        fscanf(fin, "%d", v + i);

    printf("%d-th smallest element is %d\n", k, kthSmallest(v, n, k));
    
}