#include <stdio.h>

int main()
{
    FILE *f = fopen("out.txt", "w");

    for (int i = 0; i < 10000000; ++i)
        fprintf(f, "%d ", i);
}