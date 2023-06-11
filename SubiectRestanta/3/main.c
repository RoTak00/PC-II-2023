#include <stdio.h>
#include <stdlib.h>

struct element
{
    float val;
    int ord;
};

int compare(const void *a, const void *b)
{
    return (*(struct element *)b).val - (*(struct element *)a).val;
}
int main()
{
    int n;
    float g;
    scanf("%d", &n);
    scanf("%f", &g);

    struct element *v = malloc(n * sizeof(struct element));
    if (v == NULL)
    {
        perror("malloc v");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%f", &v[i].val);
        v[i].ord = i + 1;
    }

    qsort(v, n, sizeof(struct element), compare);

    int cnt = 0;

    for (int i = 0; i < n - 1; i++)
    {
        if (v[i].val - v[i + 1].val <= g)
        {
            cnt++;
            printf("%d + %d\n", v[i].ord, v[i + 1].ord);
            i += 1;
        }
    }
    return 0;
}