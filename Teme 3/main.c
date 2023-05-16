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

/*struct IntStack
{
    int data;
    struct IntStack *next;
};

void IntStackPush(struct IntStack **top, int _data)
{
    struct IntStack *temp = (struct IntStack *)malloc(sizeof(struct IntStack));
    temp->data = _data;
    temp->next = *top;
    *top = temp;
}

void IntStackPop(struct IntStack **top)
{
    if (*top == NULL)
        return;

    struct IntStack *temp = *top;
    *top = (*top)->next;
    free(temp);
    return;
}

int IntStackEmpty(struct IntStack *top)
{
    return top == NULL;
}

int IntStackTop(struct IntStack *top)
{
    return top->data;
}*/

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

    if (counter->region[Table[current.i][current.j].region] >= 2)
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

int main()
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

    FILE *fin = fopen("in.txt", "r");
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
                        printf("Adding index %d %d BOTTOM\n", temp.i, temp.j);
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
                        printf("Adding index %d %d RIGHT\n", temp.i, temp.j);
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
                        printf("Adding index %d %d TOP\n", temp.i, temp.j);
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
                        printf("Adding index %d %d LEFT\n", temp.i, temp.j);
                        StackPush(&stack, temp);
                    }
                }
            }
        }
    }

    // Build arrays to check star placement conditions
    star_counter counter;
    counter.region = (short *)calloc(visit_number + 1, sizeof(short));
    counter.row = (short *)calloc(10, sizeof(short));
    counter.col = (short *)calloc(10, sizeof(short));

    // Begin backtracking

    point current;
    current.i = 0;
    current.j = 0;

    int iter = 0;
    while (1)
    {
        iter += 1;
        if (iter % 1000 == 0)
            printf("%d\n", iter);

        if (CheckOK(&counter, current, Table))
        {
            // printf("adding star %d %d (region %d)\n", current.i, current.j, Table[current.i][current.j].region);
            StackPush(&stack, current);
            Table[current.i][current.j].star = 1;
            counter.region[Table[current.i][current.j].region] += 1;
            counter.row[current.i] += 1;
            counter.col[current.j] += 1;
        }

        if (current.i == 9 && current.j == 9)
        {
            if (CheckSolution(&counter, visit_number))
            {
                printf("Solution!\n");
                break;
            }
            else
            {
            popStar:
                if (StackEmpty(stack))
                {
                    printf("No solution\n");
                    exit(0);
                }
                // get last star
                current = StackTop(stack);
                StackPop(&stack);
                // printf("popping star %d %d (region %d)\n", current.i, current.j, Table[current.i][current.j].region);
                //  eliminate last star
                Table[current.i][current.j].star = 0;
                counter.region[Table[current.i][current.j].region] -= 1;
                counter.row[current.i] -= 1;
                counter.col[current.j] -= 1;
            }
        }

        // move forwards in the list
        if (current.j < 9 && current.i < 10)
            current.j += 1;
        else if (current.i < 9)
            current.i += 1, current.j = 0;
        else
            goto popStar;
    }

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
            printf("%c ", Table[i][j].star ? 'x' : '_');
        printf("\n");
    }

    return 0;
}