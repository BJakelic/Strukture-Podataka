#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define MAX 10

struct Directory;
typedef struct Directory* Position;
typedef struct Directory{
    char Name[MAX];
    Position Child;
    Position Sibling;
};

struct Stog;
typedef struct Stog* PositionStog;
struct Stog
{
    Position data;
    PositionStog next;
};

Position MakeDirectory();
Position SearchDirectory();
void Print();
void Exit();
PositionStog Push();
Position Pop();
PositionStog PopStog();

int main()
{
    Directory dir;
    Stog head = {.data = &dir, .next = NULL};
    char Function[MAX], Name[MAX], CurrentName[MAX];
    Position p, CurrentDirectory = &dir;
    PositionStog CurrentStog = &head, h;
    int n = 0;
    int i = 0;

    strcpy(CurrentName, "");

    strcpy(dir.Name, "C:");
    dir.Sibling = NULL;
    dir.Child = NULL;

    while(1)
    {
        printf("%s%s", dir.Name, CurrentName);
        scanf("%s", Function);
        if(strcmp(Function, "md") == 0)
        {
            scanf("%s", Name);
            p = (Position)malloc(sizeof(Directory));
            strcpy(p->ime, Name);
            p->Sibling = NULL;
            p->Child = NULL;
            CurrentDirectory->Child = MakeDirectory(CurrentDirectory->Child, p);
        }
        else if(strcmp(Function, "cd") == 0)
        {
            scanf("%s", Name);
            n = strlen(CurrentName);
            CurrentDirectory = SearchDirectory(CurrentDirectory, Name, CurrentName, n, CurrentStog);
            CurrentStog = Push(CurrentStog, CurrentDirectory);
        }
        else if(strcmp(Function, "cd..") == 0)
        {
            if(CurrentDirectory != &dir)
            {
                CurrentStog = PopStog(CurrentStog);
                CurrentDirectory = Pop(CurrentStog);
            }
            for(i = strlen(CurrentName)-2;i>=0;i--)
            {
                if(CurrentName[i] == ':')
                    break;
                CurrentName[i] = '\0';
            }
        }
        else if(strcmp(Function, "dir") == 0)
        {
            print(CurrentDirectory->Child);
        }
        else if(strcmp(Function, "exit") == 0)
        {
            Exit(&dir);
            return 0;
        }
        else
        {
            printf("Incorrect input!\n");
        }
    }

    return 0;
}

Position MakeDirectory(Position CurrentDirectory, Position p)
{
    if(CurrentDirectory == NULL)
        return p;
    if(strcmp(CurrentDirectory->Name, p->Name) > 0)
    {
        p->Sibling = CurrentDirectory;
        return p;
    }
    else if(strcmp(CurrentDirectory->Name, p->Name) < 0)
        CurrentDirectory->Sibling = AddDirectory(CurrentDirectory->Sibling, p);
    else
    {
        printf("Name already used! (Please, try again)");
        free(p);
    }
    return CurrentDirectory;
}

Position SearchDirectory(Position CurrentDirectory, char* Name, char* CurrentName, int n, PositionStog CurrentStog)
{
    int i;
    CurrentDirectory = CurrentDirectory->Child;
    while(CurrentDirectory != NULL)
    {
        if(strcmp(CurrentDirectory->Name, Name) == 0)
        {
            for(i = 0; i < strlen(Name); i++)
                CurrentName[n + i] = Name[i];
            CurrentName[n + i] = ':';
            CurrentName[n + 1 + i] = '\0';
            CurrentStog = push(CurrentStog, CurrentDirectory);
            return CurrentDirectory;
        }
        CurrentDirectory = CurrentDirectory->Sibling;
    }
    if(CurrentDirectory == NULL)
    {
        printf("Directory not found!\n");
        return CurrentDirectory;
    }
    return CurrentDirectory;
}

void Print(Position p)
{
    if(p == NULL)
        printf("Directory not found!\n");
    while(p != NULL)
    {
        printf(" %s\n", p->Name);
        p = p->Sibling;
    }
}

void Exit(Position p)
{
    if(!p)
        return;
    Exit(p->Sibling);
    Exit(p->Child);
    free(p);
}

PositionStog Push(PositionStog CurrentStog, Position CurrentDirectory)
{
    PositionStog p;
    p = (stpoz)malloc(sizeof(struct stog));
    p->data = p;
    p->next = CurrentStog;
    return p;
}

Position Pop(PositionStog CurrentStog)
{
    Position p;
    p = CurrentStog->data;
    return p;
}

PositionStog PopStog(PositionStog CurrentStog)
{
    PositionStog p = CurrentStog->next;
    return p;
}