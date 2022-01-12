/*NAPOMENA: ZADATAK NIJE DOVRŠEN!*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define NameLength 20

struct Country;
struct City;

typedef struct Country* PosCountry;
typedef struct City* PosCity;

struct Country{
    char name[NameLength];
    PosCountry next;
    PosCity cities;
};

struct City{
    char name[NameLength];
    int population;
    PosCity left;
    PosCity right;
};

PosCountry CreateCountry(char* countryName);
void AddCountry(PosCountry head, PosCountry name);
void Print(PosCountry head);
void CreateCity(PosCountry currentCountry, char* cityName, int population);
void SortCities(PosCity city, PosCity current);

int main()
{

}

PosCountry CreateCountry(char* countryName)
{
    PosCountry newCountry = NULL;
    newCountry = (PosCountry)malloc(sizeof(Country));

    strcpy(newCountry->name, countryName);
    newCountry->next = NULL;
    newCountry->cities = NULL;

    return newCountry;
}

void AddCountry(PosCountry head, PosCountry newCountry)
{
    PosCountry temp = NULL;
    temp = head;

    while(temp->next != NULL)
    {
        if(strcmp(newCountry->name, temp->next->name) > 0)
        {
            temp = temp->next;
        }
    }

    newCountry->next = temp->next;
    temp->next = newCountry;

    newCountry->cities = OpenFile(newCountry->name)

    return;
}

void Print(PosCountry head)
{
    PosCountry temp = NULL;
    temp = head->next;
    PosCity cityList = NULL;
    cityList = temp;

    while(temp->next != NULL)
    {
        printf("%s\n", temp->name);
        while(cityList->right != NULL)
        {
            if(cityList->left != NULL)
            {
                printf("\tName: %s | Population: %d\n", cityList->left->name, cityList->left->population);
                cityList = cityList->left;
            }
            else
            {
                cityList = cityList->right;
                printf("\tName: %s | Population: %d\n", cityList->right->name, cityList->right->population);
            }
        }
    }
    
    return;
}

PosCity AddCity(PosCountry currentCountry, char* cityName, int population)
{
    PosCity newCity = NULL;
    newCity = (PosCity)malloc(sizeof(City));

    strcpy(newCity->name, cityName);
    newCity->population = population;

    newCity->left = NULL;
    newCity->right = NULL;

    if(currentCountry->cities == NULL)
    {
        currentCountry->cities = newCity;
    }
    while(currentCountry->cities != NULL)
    {
        SortCities(newCity, currentCountry->cities);
    }

    return newCity;
}

void SortCities(PosCity city, PosCity current)
{
    if(city->population > current->population && !current->left)
		current->left = city;

	else if(city->population < current->population && !current->right)
		current->right = city;

	else if(city->population > current->population)
		SortCities(current->left, city);

	else(city->population < current->population)
		SortCities(current->right, city);

    return;
}
