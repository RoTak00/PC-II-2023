#include <stdio.h>
#include <stdlib.h>

#define BOTTOM 1
#define RIGHT 2
#define TOP 4
#define LEFT 8

typedef struct
{
    unsigned int star;
    unsigned int walls;
    unsigned int region;
} cell;

typedef struct
{
    int i, j;
} point;

typedef struct
{
    short *region;
    short *row;
    short *col;
} star_counter;

struct PointStack
{
    point data;
    struct PointStack *next;
};

void StackPush(struct PointStack **top, point _data)
{
    struct PointStack *temp = (struct PointStack *)malloc(sizeof(struct PointStack));
    temp->data = _data;
    temp->next = *top;
    *top = temp;
}

void StackPop(struct PointStack **top)
{
    if (*top == NULL)
        return;

    struct PointStack *temp = *top;
    *top = (*top)->next;
    free(temp);
    return;
}

int StackEmpty(struct PointStack *top)
{
    return top == NULL;
}

point StackTop(struct PointStack *top)
{
    return top->data;
}

int CheckInside(int i, int j)
{
    return i >= 0 && i < 10 && j >= 0 && j < 10;
}
int CheckOK(star_counter *counter, point current, cell **Table)
{
    const int ki[] = {1, 1, 0, -1, -1, -1, 0, 1};
    const int kj[] = {0, 1, 1, 1, 0, -1, -1, -1};

    if (Table[current.i][current.j].star == 1)
        return 0;

    if (counter->region[Table[current.i][current.j].region] >= 2)
        return 0;

    if (counter->col[current.j] >= 2)
        return 0;

    if (counter->row[current.i] >= 2)
        return 0;

    for (int k = 0; k < 8; ++k)
    {
        int vi = current.i + ki[k];
        int vj = current.j + kj[k];
        if (CheckInside(vi, vj) && Table[vi][vj].star == 1)
            return 0;
    }
    return 1;
}

int CheckSolution(star_counter *counter, int visit_number)
{
    for (int i = 0; i < 10; ++i)
    {
        if (counter->col[i] != 2)
            return 0;
        if (counter->row[i] != 2)
            return 0;
    }

    for (int i = 1; i <= visit_number; ++i)
        if (counter->region[i] != 2)
            return 0;

    return 1;
}

void PrintTableWithRegions(cell **Table)
{
    for (int i = 0; i < 10; ++i)
    {

        for (int j = 0; j < 10; ++j)
        {
            if (Table[i][j].star)
                printf("\033[91m");

            printf("%c ", Table[i][j].region + 'a' - 1);

            if (Table[i][j].star)
                printf("\033[39m");
        }
        printf("\n");
    }
}

void PrintTableStars(cell **Table)
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
            printf("%c ", Table[i][j].star ? '*' : '_');
        printf("\n");
    }
}

void PrintRegions(cell **Table)
{
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
            printf("%c ", Table[i][j].region + 'a' - 1);
        printf("\n");
    }
}

int Backtrack(cell **Table, star_counter counter, int i, int *iters, int visit_number)
{
    *iters += 1;

    if ((*iters) % 2500000 == 0)
    {
        printf("%8d iterations yet \n", *iters);
        fprintf(stderr, "%8d iterations yet \n", *iters);
    }

    if (i == 20)
    {
        if (CheckSolution(&counter, visit_number))
        {
            printf("Solution\n");
            return 1;
        }
    }
    else
    {
        int row = i % 10;
        point current;

        int jstart = 0;
        if (i >= 10)
        {
            for (int k = 0; k < 10; ++k)
                if (Table[row][k].star == 1)
                {
                    jstart = k + 1;
                    break;
                }
        }

        for (int j = jstart; j < 10; ++j)
        {
            current.i = row;
            current.j = j;
            if (CheckOK(&counter, current, Table))
            {
                Table[current.i][current.j].star = 1;
                counter.row[row] += 1;
                counter.col[j] += 1;
                counter.region[Table[row][j].region] += 1;
                // printf("adding to index %d %d\n", row, j);
                if (Backtrack(Table, counter, i + 1, iters, visit_number))
                    return 1;

                Table[current.i][current.j].star = 0;
                counter.row[row] -= 1;
                counter.col[j] -= 1;
                counter.region[Table[row][j].region] -= 1;
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    cell **Table = (cell **)calloc(10, sizeof(cell *));
    if (Table == NULL)
    {
        perror("calloc table");
        exit(1);
    }
    for (int i = 0; i < 10; ++i)
    {
        Table[i] = (cell *)calloc(10, sizeof(cell));
        if (Table[i] == NULL)
        {
            perror("calloc row");
            exit(1);
        }
    }

    FILE *fin;
    if (argc == 2)
        fin = fopen(argv[1], "r");
    else
        fin = fopen("in.txt", "r");
    if (fin == NULL)
    {
        perror("fopen");
        exit(1);
    }

    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            fscanf(fin, "%d", &(Table[i][j].walls));

    struct PointStack *stack = NULL;

    // Here we are building the regions for the stars
    printf("Initiating fill: \n");
    char visit_number = 0;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            if (Table[i][j].region == 0)
            {
                point temp;
                temp.i = i;
                temp.j = j;
                StackPush(&stack, temp);
                visit_number += 1;
            }

            while (!StackEmpty(stack))
            {
                point current = StackTop(stack);
                StackPop(&stack);
                Table[current.i][current.j].region = visit_number;

                point temp;
                // bottom
                if (current.i < 9 && !(Table[current.i][current.j].walls & BOTTOM))
                {
                    temp.i = current.i + 1;
                    temp.j = current.j;
                    if (Table[temp.i][temp.j].region == 0)
                    {
                        StackPush(&stack, temp);
                    }
                }

                // right
                if (current.j < 9 && !(Table[current.i][current.j].walls & RIGHT))
                {
                    temp.i = current.i;
                    temp.j = current.j + 1;
                    if (Table[temp.i][temp.j].region == 0)
                    {
                        StackPush(&stack, temp);
                    }
                }

                // top
                if (current.i > 0 && !(Table[current.i][current.j].walls & TOP))
                {
                    temp.i = current.i - 1;
                    temp.j = current.j;
                    if (Table[temp.i][temp.j].region == 0)
                    {
                        StackPush(&stack, temp);
                    }
                }

                // left
                if (current.j > 0 && !(Table[current.i][current.j].walls & LEFT))
                {
                    temp.i = current.i;
                    temp.j = current.j - 1;
                    if (Table[temp.i][temp.j].region == 0)
                    {
                        StackPush(&stack, temp);
                    }
                }
            }
        }
    }

    printf("Fill done.\n");
    PrintRegions(Table);

    // Build arrays to check star placement conditions
    star_counter counter;
    counter.region = (short *)calloc(visit_number + 1, sizeof(short));
    counter.row = (short *)calloc(10, sizeof(short));
    counter.col = (short *)calloc(10, sizeof(short));

    // Begin backtracking

    int iters = 0;
    printf("Initiating backtrack.\n");
    Backtrack(Table, counter, 0, &iters, visit_number);

    printf("Found a solution!:\n");

    PrintTableWithRegions(Table);

    printf("Stars:\n");
    PrintTableStars(Table);
    printf("It took %d Backtrack calls\n", iters);

    return 0;
}