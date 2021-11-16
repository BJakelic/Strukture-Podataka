#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define MAX 1024

struct _element;
struct typedef _element* Position;

typedef struct _element{
    int number;
    struct Position next;
} element;

Position CreateElement(double number);
int InsertAfter(Position first, Position new);
int DeleteAfter(Position first);
int Push(Position head, double number);
int Pop(Position head);
int DeleteAll(Position head);
int PerformOperation(char operation, Position head);
int CalculateFromFile(char* fileName, double* result);

int main()
{
    double result = 0;
    int status = 0;
    char fileName[MAX] = {0};

    printf("Enter file name: ");
    scanf("%s", fileName);
    
    status = CalculateFromFile(fileName, &result);

    if(status == EXIT_SUCCESS)
        printf("\nResult: %lf", result);

    return EXIT_SUCCESS;
}

Position CreateElement(double number)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(stackElement));

	if (!newElement)
	{
		perror("Couldn't allocate memory!\n");
		return NULL;
	}

	newElement->number = number;
	newElement->next = NULL;

	return newElement;
}

int InsertAfter(Position first, Position new)      
{
	new->next = first->next;
	first->next = new;

	return EXIT_SUCCESS;
}

int DeleteAfter(Position first)
{
	Position temp = first->next;

	if (!temp)
	{
		return EXIT_SUCCESS;
	}

	first->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int Push(Position head, double number)
{
	Position new = NULL;
	new = CreateElement(number);

	if (!new)
	{
		perror("Couldn't allocate memory!\n");
		return -1;
	}

	InsertAfter(head, new);

	return EXIT_SUCCESS;
}

int Pop(double* destination, Position head)
{
	Position first = head->next;

	if (!first)
	{
		perror("Postfix not valid! Please check the file!\n");
		return -1;
	}

	*destination = first->number;

	DeleteAfter(head);

	return EXIT_SUCCESS;
}

int DeleteAll(Position head)
{
	while (head->next != NULL)
	{
		DeleteAfter(head);
	}

	return EXIT_SUCCESS;
}

int PerformOperation(char operation, Position head)
{
	double operand1 = 0;
	double operand2 = 0;
	double result = 0;
	int status1 = EXIT_SUCCESS;
	int status2 = EXIT_SUCCESS;

	status2 = Pop(&operand2, head);
	if (status2 != EXIT_SUCCESS)
	{
		return -2;
	}
	status1 = Pop(&operand1, head);
	if (status1 != EXIT_SUCCESS)
	{
		return -1;
	}
	switch (operation)
	{
	case '+':
	{
		result = operand1 + operand2;
		break;
	}
	case '*':
	{
		result = operand1 * operand2;
		break;
	}
	case '-':
	{
		result = operand1 - operand2;
		break;
	}
	case '/':
	{
		if (operand2 == 0)
		{
			perror("Can't divide with zero!\n");
			return -3;
		}
		result = operand1 / operand2;
		break;
	}
	default:
	{
		printf("Operation unavailable! Please contact us to report the problem.\n");
		return -4;
	}
	}

	Push(head, result);
	return EXIT_SUCCESS;
}

int CalculateFromFile(char* fileName, double* result)
{
	FILE* fp = NULL;
	char* buffer = NULL;
	char* currentBuffer = NULL;
	char operation = 0;
	int fileLength = 0;
	int status = 0;
	double number = 0;
	int numBytes = 0;
	element head = { .number = 0, .next = NULL };

	fp = fopen(fileName, "rb");
	if (!fp)
	{
		perror("Couldn't open the file!\n");
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	fileLength = ftell(fp);

	buffer = (char*)calloc(fileLength + 1, sizeof(char));
	if (!buffer)
	{
		perror("Couldn't allocate memory!\n");
		return -2;
	}

	rewind(fp);
	fread(buffer, sizeof(char), fileLength, fp);
	printf("|%s|\n", buffer);
	
	fclose(fp);

	currentBuffer = buffer;

	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, "%lf %n", &number, &numBytes);
		if (status == 1)
		{
			status = Push(&head, number);
			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				DeleteAll(&head);
				return -3;
			}
			currentBuffer += numBytes;
		}
		else
		{
			status = sscanf(currentBuffer, "%c %n", &operation, &numBytes);
			if (status == 1)
			{
				status = PerformOperation(operation, &head);
				if (status != EXIT_SUCCESS)
				{
					free(buffer);
					DeleteAll(&head);
					return -4;
				}
				currentBuffer += numBytes;
			}
			else
			{
				printf("Postfix not valid!\n");
				DeleteAll(&head);
				return -7;
			}
		}
	}
	free(buffer);

	status = Pop(result, &head);
	if (status != EXIT_SUCCESS)
	{
		DeleteAll(&head);
		return -5;
	}

	if (head.next)
	{
		printf("Postfix not valid! Please check your file!\n");
		DeleteAll(&head);
		return -6;
	}

	return EXIT_SUCCESS;
}