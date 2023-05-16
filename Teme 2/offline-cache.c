#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int optimal_offline_cache(int nr_resurse, char **resurse, int dim_cache, char **cache, int nr_accesari, char **accesari, int *out_cache_misses, char ****out_cache)
{
    *out_cache_misses = 0;

    /**out_cache = (char ***)malloc(sizeof(char **) * nr_accesari);
    for (int i = 0; i < nr_accesari; ++i)
    {
        *(out_cache)[i] = (char **)malloc(sizeof(char *) * dim_cache);
        for (int j = 0; j < dim_cache; ++j)
            (*out_cache)[i][j] = (char *)malloc(sizeof(char) * 64);
    }*/

    // Calculam pentru fiecare resursa, la fiecare accesare, cand va fi accesata urmatoare data
    // Incepem de la final, mergem spre inceput
    // Ultimul trebuie sa fie inf inf inf

    int **cache_next_requests = (int **)malloc(sizeof(int *) * nr_accesari);
    for (int i = 0; i < nr_accesari; ++i)
    {
        cache_next_requests[i] = (int *)calloc(nr_resurse, sizeof(int));
    }
    for (int i = 0; i < nr_resurse; ++i)
        cache_next_requests[nr_accesari - 1][i] = 0x3f3f3f3f;

    for (int i = nr_accesari - 2; i >= 0; --i)
    {
        // Copiem valorile de dupa
        for (int j = 0; j < nr_resurse; ++j)
            cache_next_requests[i][j] = cache_next_requests[i + 1][j] + 1;

        // Il crestem pe cel care urmeaza sa fie actualizat
        for (int j = 0; j < nr_resurse; ++j)
            if (strcmp(resurse[j], accesari[i + 1]) == 0)
                cache_next_requests[i][j] = 0;
    }

    printf("-------------------\n");
    printf("INFO: GENERATED LIST OF NEXT REQUESTS FOR EVERY ELEMENT\nel ");
    for (int j = 0; j < nr_resurse; ++j)
        printf("%s ", resurse[j]);
    printf("\n");
    for (int i = 0; i < nr_accesari; ++i)
    {
        printf("%d. ", i + 1);
        for (int j = 0; j < nr_resurse; ++j)
        {
            if (cache_next_requests[i][j] < 0x3f3f3f3f - 10)
                printf("%d ", cache_next_requests[i][j]);
            else
                printf("inf ");
        }
        printf("(%s)\n", accesari[i]);
    }
    printf("\n-------------------------------\n");
    for (int i = 0; i < nr_accesari; ++i)
    {
        printf("REQ: %s\n", accesari[i]);
        // check if the current element is found in the cache
        int bFoundCache = 0;
        for (int j = 0; j < dim_cache; ++j)
        {
            if (strcmp(accesari[i], cache[j]) == 0)
            {
                bFoundCache = 1;
                break;
            }
        }

        if (bFoundCache)
        {
            printf("INFO: Found %s in cache \n", accesari[i]);
        }

        else
        {
            // if it is not found in the cache, let's see what we can swap it with
            printf("INFO: %s not found in cache.\n", accesari[i]);
            int swap_index = -1;
            int cache_index = -1;
            for (int j = 0; j < nr_resurse; ++j)
            {
                int temp_cache_index = -1;
                int bCurrentlyInCache = 0;
                for (int k = 0; k < dim_cache; ++k)
                    if (strcmp(resurse[j], cache[k]) == 0)
                        bCurrentlyInCache = 1, temp_cache_index = k;

                if (bCurrentlyInCache == 0)
                    continue;

                if (swap_index == -1)
                {
                    swap_index = j;
                    cache_index = temp_cache_index;
                    printf("SWAPOPT: default (%s)\n", resurse[j]);
                }
                else if (cache_next_requests[i][j] > cache_next_requests[i][swap_index])
                {
                    swap_index = j;
                    cache_index = temp_cache_index;
                    printf("SWAPOPT: better (%s)\n", resurse[j]);
                }
            }

            printf("SWAP: final (%s)\n", resurse[swap_index]);

            strcpy(cache[cache_index], accesari[i]);
            *out_cache_misses += 1;
        }

        /*for (int j = 0; j < dim_cache; ++j)
        {
            strcpy((*out_cache)[i][j], cache[j]);
        }*/
        printf("CACHE: (%d.)\n", i);
        for (int j = 0; j < dim_cache; ++j)
            printf("%s ", cache[j]);
        printf("\n------------------------------\n");
    }
}
int main()
{
    FILE *fin = fopen("in.txt", "r");
    if (fin == NULL)
    {
        perror("fin");
        exit(EXIT_FAILURE);
    }

    int nr_resurse;
    fscanf(fin, "%d", &nr_resurse);

    char **resurse = (char **)malloc(sizeof(char *) * nr_resurse);
    if (resurse == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nr_resurse; ++i)
    {
        resurse[i] = (char *)calloc(64, sizeof(char));
        fscanf(fin, "%s", resurse[i]);
    }

    int dim_cache;
    fscanf(fin, "%d", &dim_cache);

    char **cache = (char **)malloc(sizeof(char *) * dim_cache);
    if (cache == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < dim_cache; ++i)
    {
        cache[i] = (char *)calloc(64, sizeof(char));
        fscanf(fin, "%s", cache[i]);
    }

    int nr_accesari;
    fscanf(fin, "%d", &nr_accesari);

    char **accesari = (char **)malloc(sizeof(char *) * nr_accesari);
    if (accesari == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nr_accesari; ++i)
    {
        accesari[i] = (char *)calloc(64, sizeof(char));
        fscanf(fin, "%s", accesari[i]);
    }

    int cache_misses;
    char ****cache_results;

    optimal_offline_cache(nr_resurse, resurse, dim_cache, cache, nr_accesari, accesari, &cache_misses, cache_results);

    /*for (int i = 0; i < nr_accesari; ++i)
    {
        printf("Accesarea %d (%s): ", i, accesari[i]);
        for (int j = 0; j < dim_cache; ++j)
        {
            printf("%s ", (*cache_results)[i][j]);
        }
    }*/
}