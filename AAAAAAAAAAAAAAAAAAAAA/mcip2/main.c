/*
Din fisierul nrsubsircresc.in se citeste un numar natural n(n<=300) si apoi un sir cu n elemente numere naturale cu cel mult 9 cifre fiecare.
Calculati si afisati in fisierul nrsubsircresc.out numarul de subsiruri strict crescatoare care se pot forma in sirul citit.
Exeplu:
nrsubsircresc.in
5
1 2 3 4 2
nrsubsircresc.out
17*/

#include <stdio.h>
#include <stdlib.h>

int n;
int v[300];
int lsir[300];

int main()
{
    FILE *f = fopen("nrsubsircresc.in", "r");
    if (!f)
    {
        printf("Eroare la deschiderea fisierului nrsubsircresc.in\n");
        exit(1);
    }

    fscanf(f, "%d", &n);
    for (int i = 1; i <= n; i++)
        fscanf(f, "%d", &v[i]);
    fclose(f);

    for (int i = 1; i <= n; i++)
    {
        lsir[i] = 1;
        for (int j = 1; j < i; j++)
        {

            if (v[i] > v[j] && lsir[i] < lsir[j] + 1)
                lsir[i] = lsir[j] + 1;

            if (v[i] > v[j] && lsir[j] >)
                lsir[i] = lsir[j] + 1;
        }
    }

    int sum = 0;
    for (int i = 1; i <= n; i++)
        sum += lsir[i];
}