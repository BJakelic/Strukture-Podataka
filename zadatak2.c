#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)

struct _person;
typedef struct _person* position;
typedef struct _person {			//struktura osoba
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	position next;
}person;

int PrependList(position head, char* name, char* surname, int birthYear);
int PrintList(position first);
position CreatePerson(char* name, char* surname, int birthYear);
position FindLast(position head);
int ApendList(position head, char* name, char* surname, int birthYear);
int InsertAfter(position position, position newPerson);
position FindPerson(position first, char* surname)

int main(int argc, char** argv)
{
	person head = {.next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	position p = &head;

	return EXIT_SUCCESS;
}

position CreatePerson(char* name, char* surname, int birthYear)
{
	position newPerson = NULL;

	newPerson = (position)malloc(sizeof(person));
	if (!newPerson)
	{
		perror("Can't allocate memory! \n");
		return NULL;
	}
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return EXIT_SUCCESS;
}

int PrependList(position head, char* name, char* surname, int birthYear)
{
	position newPerson = NULL;
	
	newPerson = CreatePerson(name, surname, birthYear);

	if (!newPerson)
		return -1;

	InsertAfter(head, newPerson);

	return EXIT_SUCCESS;
}

int PrintList(position first)
{
	position temp = first;
	while (temp)
	{
		printf("name: %s, surname: %s, birth year: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

position FindLast(position head)
{
	position temp = head;

	while (temp->next)
	{
		temp = temp->next;
	}
	return temp;
}

int ApendList(position head, char* name, char* surname, int birthYear)
{
	position newPerson = NULL;
	position last = NULL;
	newPerson = CreatePerson(name, surname, birthYear);

	if (!newPerson)
		return -1;

	last = FindLast(head);
	InsertAfter(last, newPerson);

	return EXIT_SUCCESS;
}

int InsertAfter(position position, position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson->next;
	return EXIT_SUCCESS;
}

position FindPerson(position first, char* surname)
{
	position temp = first;
	while (temp)
	{
		if (strcmp(temp->surname, surname) == 0)
		{
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}
