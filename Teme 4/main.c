#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct
{
    char name[32];
    char symbol[8];
    char lower[8];
} Element;

int read_elements(Element *element_arr, char *path)
{
    FILE *file = fopen(path, "r");

    char buffer[128];

    int index = 1;
    while (fgets(buffer, 128, file))
    {
        buffer[strlen(buffer) - 1] = 0;
        char *p = strtok(buffer, ",");
        strcpy(element_arr[index].name, p);
        p = strtok(NULL, ",");
        strcpy(element_arr[index].symbol, p);
        char *n = p;
        for (; *p; p++)
            *p = tolower(*p);
        strcpy(element_arr[index].lower, n);
        index += 1;
    }

    strcpy(element_arr[0].name, "Space");
    strcpy(element_arr[0].symbol, " ");

    fclose(file);
    return index;
}

int Solve(Element *arr, int len, char *string, int index, int *res, int res_index)
{
    if (index >= strlen(string))
    {
        printf("found sol\n");
        return 1;
    }
    printf("index: %d\n", index);
    // element cu 1 caracter
    int bOneCharacter = 0;
    char option1[8];
    strncpy(option1, string + strlen(string) - index - 1, 1);
    strcpy(option1 + 1, "\0");
    printf("%s ", option1);

    // element cu 2 caractere
    int bTwoCharacters = 0;
    char option2[8];
    strncpy(option2, string + strlen(string) - index - 2, 2);
    strcpy(option2 + 2, "\0");
    printf("%s\n", option2);

    for (int i = 0; i < len; ++i)
    {
        if (strcmp(option1, arr[i].lower) == 0)
        {
            bOneCharacter = 1;
            printf("Found %s\n", arr[i].symbol);
        }

        if (index < strlen(string) - 1 && strcmp(option2, arr[i].lower) == 0)
        {
            bTwoCharacters = 1;
            printf("Found %s\n", arr[i].symbol);
        }
    }

    return (bTwoCharacters && Solve(arr, len, string, index + 2, res, res_index + 1)) || (bOneCharacter && Solve(arr, len, string, index + 1, res, res_index + 1));
}

int main()
{
    Element elements[125];
    int n_elements = read_elements(elements, "elements.txt");

    int res[128] = {0};

    char string_to_convert[256];
    scanf("%s", string_to_convert);
    Solve(elements, n_elements, string_to_convert, 0, res, 0);

    return 0;
}