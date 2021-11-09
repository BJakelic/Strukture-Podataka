#define CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10

typedef struct polynomial* poly;
struct polynomial{
    int coef;
    int exp;
    struct polynomial* next;
};

int ReadAndSortFile(poly p);
int CreatePoly(poly head);
int Sum(poly p1, poly p2, poly sum);
int SumIn(poly sum, int coef, int exp);
int Product(poly p1, poly p2, poly prod);
int SortProd(poly prod);
int Print(poly p);

int main()
{
    poly p1;
    poly p2;
    poly sum;
    poly prod;

	p1 = (poly)malloc(sizeof(polynomial));
	p2= (poly)malloc(sizeof(polynomial));
	sum = (poly)malloc(sizeof(polynomial));
	prod = (poly)malloc(sizeof(polynomial));

	p1->next = NULL;
	p2->next = NULL;
	sum->next = NULL;
	prod->next = NULL;

	ReadAndSortFile(p1);
    ReadAndSortFile(p2);

	Sum(p1, p2, sum);
	printf("Suma:\n");
	Print(sum);

	Product(p1, p2, prod);
	SortProd(prod);
	printf("Umnožak:\n");
	Print(prod);

	return 0;
}

int ReadAndSortFile(poly p)
{
    poly temp = NULL;
    temp = p;

    poly q;
    q = (poly)malloc(sizeof(polynomial));

    char* file;
    file = (char*)malloc(sizeof(char)*N);

    printf("Unesite ime datoteke za iščitavanje polinoma: ");
    scanf("%s", file);

    FILE* fp = NULL;
    fp = fopen("file", "r");

    if(fp==NULL)
        printf("GREŠKA! (otvaranje datoteke)");

    while(!feof(fp))
    {
        q = CreatePoly(q);

        fscanf(fp, " %d %d", &q->coef, &q->exp);

        while(temp->next!=NULL && temp->next->exp > q->exp)
            temp = temp->next;
        if(temp->next!=NULL && temp->next->exp == q->exp)
            temp->next->coef += q->coef;
        if(temp->next->coef == 0)
        {
            q = temp->next;
            temp->next = q->next;
        }
        else{
            q->next = temp->next;
            temp->next = q;
        }
    }

    fclose(fp);

    return 0;
}

int CreatePoly(poly head)
{
    poly q;
    q = (poly)malloc(sizeof(polynomial));

    if(head == NULL)
        printf("GREŠKA! (alokacija memorije)");

    q->next = head->next;
    head->next = q;

    return q;
}

int Sum(poly p1, poly p2, poly sum)
{
    poly temp = NULL;
    temp = (poly)malloc(sizeof(polynomial));
	p1 = p1->next;
	p2 = p2->next;

	while (p1 != NULL && p2 != NULL) {

		if (p1->exp == p2->exp) {
			UnosSume(sum, p1->coef + p2->coef, p1->exp);
			p1 = p1->next;
			p2 = p2->next;
		}

		else if (p1->pot > p2->pot) {
			UnosSume(sum, p1->coef, p1->exp);
			p1 = p1->next;
		}

		else {
			UnosSume(sum, p2->coef, p2->exp);
			p2 = p2->next;
		}
	}

	if (p1 != NULL)
		temp = p1;
	else
		temp = p2;

	while (temp != NULL) {
		UnosSume(sum, temp->coef, temp->exp);
		temp = temp->next;
	}

	return 0;
}

int SumIn(poly sum, int coef, int exp)
{
    poly q;

	while (sum->next != NULL && sum->next->exp > exp)
		sum = sum->next;
	
	q = (poly)malloc(sizeof(polynomial));
	q->coef = coef;
	q->exp = exp;
	q->next = sum->next;
	sum->next = q;

	return 0;
}

int Product(poly p1, poly p2, poly prod)
{
	poly temp;
	p1 = p1->next;
	p2 = p2->next;
	temp = p2->next;

	while (p1 != NULL) {
		while (p2 != NULL) {
			UnosSume(prod, p1->coef * p2->coef, p1->exp + p2->exp);
			p2 = p2->next;
		}
		p2 = temp;
		p1 = p1->next;
	}
	return 0;
}

int SortProd(poly prod)
{
	poly temp;
	temp = (poly)malloc(sizeof(polynomial));

	prod = prod->next;
	temp = prod->next;

	while (prod != NULL && temp!=NULL) {
		if(prod->exp == temp->exp) {
			prod->coef = prod->coef + temp->coef;
			prod->next = temp->next;
			free(temp);
			temp = prod->next;
		}	
		else {
			prod = prod->next;
			temp = temp->next;
		}
	}

	return 0;
}

int Print(poly p)
{
    p = p->next;
	while (p->next != NULL) {
		printf(" %d x^%d + ", p->coef, p->exp);
		p = p->next;
	}
	printf(" %d x^%d \n", p->coef, p->exp);

	return 0;
}