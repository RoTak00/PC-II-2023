#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))


int X[16] = {0};
int S[16] = {0};

    int p, c;

void Solutie(int k)
{
    for(int i = 0; i <= k; ++i)
        printf("%d", X[i]);
    printf(" ");

}

int Back(int k)
{
    if(k == 0)
    {
        for(int i = 1; i <= 9; ++i)
        {
            X[k] = i;
            S[k] = i;

            if(S[k] == c)
                Solutie(k);
            else if (S[k] < c)
                Back(k + 1);
            else
                break;
            
        }
    }
    else if(k > 0)
    {
        for(int i = MAX(1, X[0] - p); i <= MIN(9, X[0] + p); ++i)
        {
            X[k] = i;
            S[k] = S[k - 1] + i;

            if(S[k] == c)
                Solutie(k);
            else if (S[k] < c)
                Back(k + 1);
            else
                break;
        }
    }
}
int main()
{
    scanf("%d%d", &p, &c);

    Back(0);
}