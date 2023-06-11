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
        if (buffer[strlen(buffer) - 1] == '\n')
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

    strcpy(element_arr[0].name, "|");
    strcpy(element_arr[0].symbol, "|");
    strcpy(element_arr[0].lower, " ");

    fclose(file);
    return index;
}

void Solve(Element *els, int els_len, char *string)
{
    int string_len = strlen(string);

    int *E1 = (int *)calloc(string_len, sizeof(int));
    int *E2 = (int *)calloc(string_len, sizeof(int));
    int *Jumps = (int *)calloc(string_len + 1, sizeof(int));

    for (int i = 0; i < string_len; ++i)
    {
        char option1[8] = "", option2[8] = "";
        strncpy(option1, string + i, 1);
        strcpy(option1 + 1, "\0");

        if (i != string_len - 1)
        {
            strncpy(option2, string + i, 2);
            strcpy(option2 + 2, "\0");
            // printf("%s ", option2);
        }

        for (int k = 0; k < els_len; ++k)
        {
            if (strcmp(option1, els[k].lower) == 0)
                E1[i] = k + 1;

            if (i != string_len - 1)
                if (strcmp(option2, els[k].lower) == 0)
                    E2[i] = k + 1;
        }
    }

    int c_index = 0;
    int j_index = 0;
    while (c_index < string_len)
    {
        // both exist
        if (E2[c_index] && E1[c_index])
        {
            if (E2[c_index + 2] || E1[c_index + 2] || c_index + 2 >= string_len)
            {

                Jumps[j_index++] = E2[c_index];

                c_index += 2;
            }
            else if (E2[c_index + 1] || E1[c_index + 1] || c_index + 1 >= string_len)
            {
                Jumps[j_index++] = E1[c_index];

                c_index += 1;
            }
            else
            {
                Jumps[0] = -1;
                break;
            }
        }
        else if (E2[c_index])
        {
            if (E2[c_index + 2] || E1[c_index + 2] || c_index + 2 >= string_len)
            {
                Jumps[j_index++] = E2[c_index];

                c_index += 2;
            }
            else
            {
                Jumps[0] = -1;
                break;
            }
        }
        else if (E1[c_index])
        {
            if (E2[c_index + 1] || E1[c_index + 1] || c_index + 1 >= string_len)
            {
                Jumps[j_index++] = E1[c_index];

                c_index += 1;
            }
            else
            {
                Jumps[0] = -1;
                break;
            }
        }
        else
        {
            Jumps[0] = -1;
            break;
        }
    }

    if (Jumps[0] == -1)
    {
        printf("Nu exista solutie!\n");
        return;
    }

    for (int i = 0; i < j_index; ++i)
    {
        printf("%s ", els[Jumps[i] - 1].symbol);
    }
    printf("\n");
    for (int i = 0; i < j_index; ++i)
    {
        printf("%s ", els[Jumps[i] - 1].name);
    }

    printf("\n");
    return;
}
int main()
{
    Element elements[125];
    int n_elements = read_elements(elements, "elements.txt");

    int res[128] = {0};

    char string_to_convert[1024];
    FILE *fin = fopen("in.txt", "r");
    if (!fin)
    {
        perror("fin");
        exit(1);
    }
    fgets(string_to_convert, 1024, fin);
    char *p = string_to_convert;
    for (; *p; p++)
        *p = tolower(*p);

    printf("%s\n", string_to_convert);

    Solve(elements, n_elements, string_to_convert);

    return 0;
}