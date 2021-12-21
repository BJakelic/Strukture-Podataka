#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

struct Tree;
typedef struct Tree* Pos;
struct Tree
{
    int element;
    Pos left;
    Pos right;
};

struct List;
typedef struct List* listPos;
struct List
{
    int element;
    listPos next;
};

Pos Insert(Pos p, int x);
int Replace(Pos p);
void Print(Pos p, listPos r);
void ApendList(listPos p, int x);
void WriteFile(FILE* f, listPos p);

int main(void)
{
    Pos root;
    root = (Pos)malloc(sizeof(struct Tree));
    int i, x;
    FILE* f;
    struct list head = {.element = 0, .next = NULL};
    srand(time(NULL));

    root->element = rand() % 80 + 10;
    root->left = NULL;
    root->right = NULL;
    printf("%d ", root->element);

    for(i=1;i<10;i++)
    {
        x = rand() % 80 + 10;
        printf("%d ", x);
        root = Insert(root, x);
    }
    printf("\n");

    Print(root, &head);
    WriteFile(f, head.next);

    root->element = Replace(root->left) + Replace(root->right);

    printf("\n");
    Print(root, &head);

    WriteFile(f, head.next);

    return 0;
}

Pos Insert(Pos p, int x)
{
    Pos q;

    if(p == NULL)
    {
        q = (Pos)malloc(sizeof(struct Tree));
        q->element = x;
        q->left = NULL;
        q->right = NULL;
        return q;
    }

    if(x >= p->element)
        p->right = Insert(p->right, x);

    if(x < p->element)
        p->left = Insert(p->left, x);

    return p;
}

int Replace(Pos p)
{
    int temp;

    if(p == NULL)
        return 0;

    temp = p->element;
    p->element = Replace(p->left) + Replace(p->right);

    return temp + p->element;
}

void Print(Pos p, listPos r)
{
    if(p == NULL)
        return;

    Print(p->right, r);
    printf("%d ", p->element);
    ApendList(r ,p->element);
    Print(p->left, r);
}

void ApendList(listPos p, int x)
{
    listPos q;

    while(p != NULL)
    {
        if(p->next == NULL)
        {
            q = (listPos)malloc(sizeof(struct List));
            q->element = x;
            p->next = q;
            q->next = NULL;
            return;
        }
        p = p->next;
    }
}

void WriteFile(FILE* f, listPos p)
{
    f = fopen("tree", "w");

    while(p != NULL)
    {
        fprintf(f, "%d ", p->element);
        p = p->next;
    }

    fprintf(f, "\n");

    fclose(f);
}