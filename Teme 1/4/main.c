#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Node
{
    int val;
    struct Node * left, * right;
};
/*
struct Node * Construire(FILE * fin, struct Node * head)
{
    char buf[32];
    fscanf(fin, "%s", buf);
    printf("%s\n", buf);
    if(strcmp(buf, "null") != 0)
    {
        head->left = (struct Node*)malloc(sizeof(struct Node));
        head->left->val = atoi(buf);
        Construire(fin, head->left);
    }
    else
        head->left = NULL;

    fscanf(fin, "%s", buf);
    printf("%s\n", buf);
    if(strcmp(buf, "null") != 0)
    {
        head->right = (struct Node*)malloc(sizeof(struct Node));
        head->right->val = atoi(buf);
        Construire(fin, head->right);
    }
    else
        head->right = NULL;

    return head;
}*/

struct Node* Construire(FILE * fin, struct Node * head)
{
    head = (struct Node*)malloc(sizeof(struct Node));
    char buf[32];
    fscanf(fin, "%s", buf);
    //printf("%s\n", buf);
    if(strcmp(buf, "null") == 0)
    {
        free(head);
        return NULL;
    }
    head->val = atoi(buf);
    head->left = Construire(fin, head->left);
    head->right = Construire(fin, head->right);
    return head;
}

void Parcurgere(struct Node * head)
{
    if(head == NULL)
    {
        printf("null\n");
        return;
    }
    printf("%d\n", head->val);
    Parcurgere(head->left);
    Parcurgere(head->right);
    return;
}

int Verificare(struct Node * head)
{
    int bLeft = 0, bRight = 0;
    if(head->left == NULL)
        bLeft = 1;
    if(head->right == NULL)
        bRight = 1;

    if(head->left != NULL)
        bLeft = head->val >= head->left->val && Verificare(head->left);
    if(head->right != NULL)
        bRight = head->val <= head->right->val && Verificare(head->right);

    return bLeft && bRight;
    
}
int main()
{
    struct Node* head = NULL;

    FILE * fin = fopen("Date.in", "r");
    if(fin == NULL)
    {
        perror("fopen");
        return 1;
    }
    /*

    char buf[32];
    fscanf(fin, "%s", buf);
    printf("%s\n", buf);

    head = (struct Node*)malloc(sizeof(struct Node));
    head->val = atoi(buf);
    Construire(fin, head);
    */

    head = Construire(fin, head);

    Parcurgere(head);

    printf("%d\n", Verificare(head));
}

