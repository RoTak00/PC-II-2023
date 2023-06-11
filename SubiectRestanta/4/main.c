#include <stdlib.h>
#include <stdio.h>

int closestDiff = 0x3f3f3f3f;
int closestSum = 0;
int main()
{
    FILE *fin = fopen("in.txt", "r");
    if (!fin)
    {
        perror("fin");
        exit(1);
    }

    int n_activitati, minute;
    int activitati[1000];

    fscanf(fin, "%d", &minute);
    fscanf(fin, "%d", &n_activitati);
    for (int i = 1; i <= n_activitati; ++i)
        fscanf(fin, "%d", &activitati[i]);
}