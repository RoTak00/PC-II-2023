#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structs used for the cache
typedef char string64[64];
typedef struct
{
    unsigned int len;
    string64 *list;
} arrayString64;

struct CacheLinkedList
{
    string64 *cache;
    struct CacheLinkedList *next;
};

int CacheLinkedListAppend(struct CacheLinkedList **head, string64 *new_cache)
{
    struct CacheLinkedList *new_node = (struct CacheLinkedList *)malloc(sizeof(struct CacheLinkedList));
    if (new_node == NULL)
    {
        perror("malloc cachelinkedlist");
        return 0;
    }

    struct CacheLinkedList *last = *head;

    new_node->cache = new_cache;
    new_node->next = NULL;

    if (*head == NULL)
    {
        *head = new_node;
        return 1;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;
    return 1;
}

void CacheLinkedListPrint(struct CacheLinkedList *head, int len)
{
    int index = 0;
    while (head != NULL)
    {
        index += 1;
        printf("%d. ", index);
        for (int i = 0; i < len; ++i)
        {
            printf("%s ", head->cache[i]);
        }
        printf("\n");
        head = head->next;
    }
}

typedef struct
{
    // inputs
    arrayString64 resources;
    arrayString64 cache;
    arrayString64 requests;

    // outputs
    struct CacheLinkedList *cache_list;
    unsigned int cache_misses;

    // internal
    int **request_frecquency;
} OptimalOfflineCache;

// Linked list used for output

void _construct_frecquency(OptimalOfflineCache **ooc)
{
    (*ooc)->request_frecquency = (int **)malloc(sizeof(int *) * (*ooc)->requests.len);
    if ((*ooc)->request_frecquency == NULL)
    {
        perror("malloc request frecquency");
        exit(1);
    }

    for (int i = 0; i < (*ooc)->requests.len; ++i)
    {
        (*ooc)->request_frecquency[i] = (int *)calloc((*ooc)->resources.len, sizeof(int));
        if ((*ooc)->request_frecquency[i] == NULL)
        {
            perror("malloc request frecquency line");
            exit(1);
        }
    }
    for (int i = 0; i < (*ooc)->resources.len; ++i)
        (*ooc)->request_frecquency[(*ooc)->requests.len - 1][i] = 0x3f3f3f3f;

    for (int i = (*ooc)->requests.len - 2; i >= 0; --i)
    {
        // Copiem valorile de dupa
        for (int j = 0; j < (*ooc)->resources.len; ++j)
            (*ooc)->request_frecquency[i][j] = (*ooc)->request_frecquency[i + 1][j] + 1;

        // Il resetam pe cel care urmeaza sa fie actualizat
        for (int j = 0; j < (*ooc)->resources.len; ++j)
            if (strcmp((*ooc)->resources.list[j], (*ooc)->requests.list[i + 1]) == 0)
                (*ooc)->request_frecquency[i][j] = 0;
    }
}

void initialize(OptimalOfflineCache **ooc, arrayString64 _resources, arrayString64 _cache, arrayString64 _requests)
{
    if (*ooc == NULL)
        *ooc = (OptimalOfflineCache *)malloc(sizeof(OptimalOfflineCache));
    if (*ooc == NULL)
    {
        perror("ooc null");
        exit(1);
    }

    (*ooc)->resources = _resources;
    (*ooc)->cache = _cache;
    (*ooc)->requests = _requests;

    (*ooc)->cache_misses = 0;

    _construct_frecquency(ooc);
}

void compute(OptimalOfflineCache **ooc)
{
    for (int i = 0; i < (*ooc)->requests.len; ++i)
    {
        int bFoundInCache = 0;

        for (int j = 0; j < (*ooc)->cache.len; ++j)
        {
            if (strcmp((*ooc)->requests.list[i], (*ooc)->cache.list[j]) == 0)
            {
                bFoundInCache = 1;
                break;
            }
        }

        if (bFoundInCache)
        {
            // printf("Found");
            ;
        }

        else
        {
            // printf("INFO: %s not found in cache.\n", accesari[i]);
            int swap_index = -1;
            int cache_index = -1;
            for (int j = 0; j < (*ooc)->resources.len; ++j)
            {
                int temp_cache_index = -1;
                int bCurrentlyInCache = 0;
                for (int k = 0; k < (*ooc)->cache.len; ++k)
                    if (strcmp((*ooc)->resources.list[j], (*ooc)->cache.list[k]) == 0)
                        bCurrentlyInCache = 1, temp_cache_index = k;

                if (bCurrentlyInCache == 0)
                    continue;

                if (swap_index == -1)
                {
                    swap_index = j;
                    cache_index = temp_cache_index;
                    // printf("SWAPOPT: default (%s)\n", resurse[j]);
                }
                else if ((*ooc)->request_frecquency[i][j] > (*ooc)->request_frecquency[i][swap_index])
                {
                    swap_index = j;
                    cache_index = temp_cache_index;
                    // printf("SWAPOPT: better (%s)\n", resurse[j]);
                }
            }

            // printf("SWAP: final (%s)\n", resurse[swap_index]);

            strcpy((*ooc)->cache.list[cache_index], (*ooc)->requests.list[i]);
            (*ooc)->cache_misses += 1;
        }

        string64 *temp_cache = (string64 *)malloc(sizeof(string64) * (*ooc)->cache.len);
        for (int i = 0; i < (*ooc)->cache.len; ++i)
            strcpy(temp_cache[i], (*ooc)->cache.list[i]);
        if (!CacheLinkedListAppend(&(*ooc)->cache_list, temp_cache))
        {
            exit(1);
        }
    }
}

int main(int argc, char *argv[])
{
    OptimalOfflineCache *ooc = NULL;
    arrayString64 resources, cache, requests;
    FILE *fin;
    if (argc == 2)
        fin = fopen(argv[1], "r");
    else
        fin = fopen("in.txt", "r");
    if (fin == NULL)
    {
        perror("fin");
        exit(EXIT_FAILURE);
    }

    fscanf(fin, "%d", &(resources.len));

    resources.list = (string64 *)malloc(sizeof(string64) * resources.len);
    if (resources.list == NULL)
    {
        perror("malloc resources");
        exit(1);
    }

    for (int i = 0; i < resources.len; ++i)
    {
        fscanf(fin, "%s", resources.list[i]);
    }

    fscanf(fin, "%d", &(cache.len));

    cache.list = (string64 *)malloc(sizeof(string64) * cache.len);
    if (resources.list == NULL)
    {
        perror("malloc cache");
        exit(1);
    }

    for (int i = 0; i < cache.len; ++i)
    {
        fscanf(fin, "%s", cache.list[i]);
    }

    fscanf(fin, "%d", &(requests.len));

    requests.list = (string64 *)malloc(sizeof(string64) * requests.len);
    if (resources.list == NULL)
    {
        perror("malloc requests");
        exit(1);
    }

    for (int i = 0; i < requests.len; ++i)
    {
        fscanf(fin, "%s", requests.list[i]);
    }

    initialize(&ooc, resources, cache, requests);

    compute(&ooc);

    printf("Cache Misses: %d\n", ooc->cache_misses);
    CacheLinkedListPrint(ooc->cache_list, ooc->cache.len);
}