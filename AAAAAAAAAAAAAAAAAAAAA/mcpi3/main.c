// read matrix from file sah.in
// matrix has 1 if there is a pawn on the board
// matrix has 0 if there is no pawn on the board
//
// a pawn can start from any place on the first line (row 1)
// determine the route to take in order to reach the last line and collect as many pieces
// i.e. pawn can move to i + 1, j if there is no piece there
// pawn can move to i + 1, j - 1 if there is a piece there
// pawn can move to i + 1, j + 1 if tehre is a piece there
// */

#include <stdio.h>
#include <stdlib.h>

unsigned char A[31][31];
unsigned char S[31][31];
int n;

void Afis(int i, int j)
{
    if (i > 1)
    {
        int cv = S[i][j];
        int nj = j;
        if (j > 1 && S[i][j - 1] == cv - 1)
            nj = j - 1;
        if (j < n && S[i][j + 1] == cv - 1)
            nj = j + 1;

        Afis(i - 1, nj);
    }
    printf("(%d, %d)\n", i, j);
}
int main()
{
    FILE *f = fopen("sah.in", "r");
    if (!f)
    {
        printf("Eroare la deschiderea fisierului sah.in\n");
        exit(1);
    }

    fscanf(f, "%d", &n);

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            fscanf(f, "%d", &A[i][j]);
    fclose(f);

    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {

            S[i][j] = S[i - 1][j];

            if (j < n && A[i][j] == 1)
                if (S[i - 1][j + 1] + 1 > S[i][j])
                    S[i][j] = S[i - 1][j + 1] + 1;

            if (j > 1 && A[i][j] == 1)
                if (S[i - 1][j - 1] + 1 > S[i][j])
                    S[i][j] = S[i - 1][j - 1] + 1;
        }

    for (int j = 1; j <= n; ++j)
    {
        printf("j: %d\n", j);
        Afis(n, j);
    }
}
