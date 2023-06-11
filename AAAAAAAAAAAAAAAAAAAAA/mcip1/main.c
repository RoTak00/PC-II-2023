/*
Se citeste un numar natural n (2<=n<=20) si apoi o matrice cu n linii
si n coloane av�nd elementele numere �ntregi cu cel mult 4 cifre fiecare.
Parcurgerea matricii se face din coltul (n,1) spre coltul (1,n) si se poate face pe directiile:
nord, nord-est si est.
a) Afisati numarul de moduri �n care se poate ajunge din coltul (n,1) �n coltul (1,n).
b) Afisati suma maxima care se poate obtine parcurg�nd matricea din coltul (n,1) �n coltul (1,n).
Pentru citire se va folosi fisierul 2.in, iar pentru afisare fisierul 2.out.
*/

#include <stdio.h>
#include <stdlib.h>

int n;
int a[21][21];
int rez1[21][21];
int rez2[21][21];

int main()
{
    FILE *f = fopen("2.in", "r");
    if (!f)
    {
        printf("Eroare la deschiderea fisierului 2.in\n");
        exit(1);
    }

    fscanf(f, "%d", &n);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            fscanf(f, "%d", &a[i][j]);

    fclose(f);

    for (int i = 1; i <= n; i++)
        rez1[1][i] = 1;
    for (int j = 1; j <= n; j++)
        rez1[j][1] = 1;

    for (int i = 2; i <= n; i++)
        for (int j = 2; j <= n; j++)
            rez1[i][j] = rez1[i][j - 1] + rez1[i - 1][j] + rez1[i - 1][j - 1];

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            printf("%d ", rez1[i][j]);
        printf("\n");
    }

    for (int i = 1; i <= n; ++i)
        rez2[1][i] = a[1][i] + rez2[1][i - 1];

    for (int j = 1; j <= n; ++j)
        rez2[j][1] = a[j][1] + rez2[j - 1][1];

    for (int i = 2; i <= n; ++i)
        for (int j = 2; j <= n; ++j)
        {
            int vmax = rez2[i][j - 1];
            if (rez2[i - 1][j] > vmax)
                vmax = rez2[i - 1][j];
            if (rez2[i - 1][j - 1] > vmax)
                vmax = rez2[i - 1][j - 1];

            rez2[i][j] = a[i][j] + vmax;
        }

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
            printf("%d ", rez2[i][j]);
        printf("\n");
    }
}