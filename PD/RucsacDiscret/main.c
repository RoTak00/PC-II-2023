#include <stdio.h>

int main()
{
    int n, i, j, G, c[101], g[101], cmax[101][1001];

    FILE *f = fopen("rucsac.txt", "r");

    fscanf(f, "%d", &G);
    fscanf(f, "%d", &n);

    for (i = 1; i <= n; i++)
        fscanf(f, "%d %d ", &g[i], &c[i]);

    fclose(f);

    for (i = 0; i <= n; i++)
        cmax[i][0] = 0;
    for (j = 0; j <= G; j++)
        cmax[0][j] = 0;

    for (i = 1; i <= n; ++i)
    {
        for (j = 1; j <= G; ++j)
        {
            if (g[i] > j)
                cmax[i][j] = cmax[i - 1][j];
            else if (c[i] + cmax[i - 1][j - g[i]] > cmax[i - 1][j])
                cmax[i][j] = c[i] + cmax[i - 1][j - g[i]];
            else
                cmax[i][j] = cmax[i - 1][j];
        }
    }

    printf("Profit %d\n", cmax[n][G]);

    i = n;
    j = G;

    while (i >= 1)
    {
        if (cmax[i][j] != cmax[i - 1][j])
        {
            printf("%d\n", i);
            j = j - g[i];
        }
        i--;
    }
}