#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include<ctype.h>
#include<stdlib.h>

#define MAX 1024


struct Tree;
typedef struct Tree* Position;
typedef struct Tree{
	int element;

    Position left;
	Position right;
};

Position Insert(Position Current, int x);
Position Delete(Position Current, int x);
Position Find(Position Current, int x);
Position FindMin(Position Current);
void Inorder(Position Current);
void Preorder(Position Current);
void Postorder(Position Current);

int main()
{
    Position root = NULL;
    int n = 0, i = 0, x = 0;

    printf("Enter the number of elements:\n");
    scanf("%d", &n);
    printf("Enter the elements:\n");
    for(i=0;i<n;i++)
    {
        scanf("%d", &x);
        root = Insert(root, x);
    }
    printf("\nINORDER:\n");
    Inorder(root);

    printf("\nPREORDER:\n");
    Preorder(root);

    printf("\nPOSTORDER:\n");
    Postorder(root);

    printf("\nWhich elements would you like to delete?\n");
    while(1)
    {
        scanf("%d", &x);
        if(x == 0)
            break;
        root = Delete(root, x);
        Inorder(root);
        if(root == NULL)
            break;
    }

    printf("\n********************\n");
    printf("FINAL:\n");

    Inorder(root);

    return 0;
}

Position Insert(Position Current, int x)
{
    Position p = NULL;
    if(Current == NULL)
    {
        p = (Position)malloc(sizeof(Tree));
        p->element = x;
        p->left = NULL;
        p->right = NULL;
        return p;
    }
    else if(x < Current->element)
        Current->left = Insert(Current->left, x);
    else if(x > Current->element)
        Current->right = Insert(Current->right, x);
    return Current;
}

Position Delete(Position Current, int x)
{
    Position temp = NULL;
    if(Current == NULL)
        printf("Element not found!\n");
    else if(x < Current->element)
        Current->left = Delete(Current->left, x);
    else if(x > Current->element)
        Current->right = Delete(Current->right, x);
    else if(Current->left != NULL && Current->right != NULL)
    {
        temp = FindMin(Current->right);
        Current->element = temp->element;
        Current->right = Delete(Current->right, Current->element);
    }
    else
    {
        temp = Current;
        if(Current->left == NULL)
            Current = Current->right;
        else
            Current = Current->left;
        free(temp);
    }
    return Current;
}

Position Find(Position Current, int x)
{
    if(Current == NULL)
        return NULL;
    else if(x < Current->element)
        return Find(Current->left, x);
    else if(x > Current->element)
        return Find(Current->right, x);
    return Current;
}

Position FindMin(Position Current)
{
	while(Current->left != NULL)
    {
        Current = Current->left;
    }
    return Current;
}

void Inorder(Position Current)
{
    if(Current == NULL)
        return;

    Inorder(Current->left);
    printf("%d ", Current->element);
    Inorder(Current->right);
    return;
}

void Preorder(Position Current)
{
    if(Current == NULL)
        return;

    printf("%d ", Current->element);
    Preorder(Current->left);
    Preorder(Current->right);
}

void Postorder(Position Current)
{
    if(Current == NULL)
        return;

    Postorder(Current->left);
    Postorder(Current->right);
    printf("%d ", Current->element);
}