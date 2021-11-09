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
position FindPerson(position first, char* surname);
position FindPrevious(position head, position person);
int InsertBefore(position head, position person);
int Sort(position head);
int ReadFile(position head);
int WriteFile(position head);

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

position FindPrevious(position head, position person)
{
	position* p;
	p = head;

	while(p != NULL && p->next != person)
		p = p->next;
	
	return p;
}

int InsertBefore(position head, position person)
{
	position newPerson;
	newPerson = (position)malloc(sizeof(person));

	position p = NULL;
	p = (position)malloc(sizeof(person));

	p = FindPrevious(head, person);

	p->next = newPerson;
	newPerson->next = person;

	return EXIT_SUCCESS;
}

int Sort(position head)
{
	position p = head;
	position q = NULL;
	position bfq = NULL;
	position last = NULL;

	while(p->next != last)
	{
		bfq = p;
		q = bfq->next;

		while(bfq->next != last)
		{
			if(strcmp(q->surname, q->next->surname)>0)
			{
				bfq->next = q->next;
				q->next = q->next->next;
				bfq->next->next = q;
				q = bfq->next;
			}
			bfq = q;
			q = q->next;
		}
		last = q;
	}
	return 0;
}

int ReadFile(position head)
{
	position q;
	position p = FindLast(head);
	
	FILE* fp = NULL;
	fp = fopen("student.txt", "r");

	int sym = 0;
	int num = 0;
	int i = 0;
	char buffer[MAX] = { 0 };

	if (fp == NULL) {
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}

	while (fgets(buffer, MAX, fp)) {
		num++;
	}

	rewind(fp);

	for(i=0; i<num; i++){
		q = (position)malloc(sizeof(person));

		q->next = NULL;
		p->next = q;
		p = p->next;

		fscanf(fp, "%s %s %d", q->ime, q->surname, &q->birthYear);		
	}

	fclose(fp);

	return 0;
}

int WriteFile(position head)
{
	position q = NULL;
	q = (position)malloc(sizeof(person));
	q = head->next;

	FILE* fp = NULL;
	fp = fopen("student.txt", "w");

	if (fp == NULL) {
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}
	
	while (q != NULL) {
		fprintf(fp, "Name: %s \tSurname: %s \tBirth Year: %d\n", q->name, q->surname, q->birthYear);
		q = q->next;
	}

	fclose(fp);

	return 0;
}
