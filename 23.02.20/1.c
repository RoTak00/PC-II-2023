#include <stdio.h>
#include <stdlib.h>

// fisier text in.txt, contine numere intregi dispuse pe mai multe linii
// numerele sunt separate in cadrul liniilor prin virgula
// scrieti un program care creaza un fisier ce contine pe fiecare linie suma numerelor situate pe ac linie

int main()
{
    FILE * fin = fopen("in.txt", "r");
    if(fin == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    FILE * fout = fopen("out.txt", "w");
    if(fout == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    unsigned int sum = 0;
    unsigned int buf;

    while(!feof(fin))
    {
        sum = 0;

        do
        {
            fscanf(fin, "%d", &buf);
            sum += buf;
        }
        while((fgetc(fin) != '\n') && !feof(fin));

        if(ftell(fout) != 0) fputc('\n', fout);
        fprintf(fout, "%d", sum);
    }

    fclose(fin);
    fclose(fout);
    exit(EXIT_SUCCESS);


    
}