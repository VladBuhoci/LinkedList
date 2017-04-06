#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Person.h"
#include "LinkedList.h"


#define POPULATION 10

#define RANDOM_NUMBER(Min, Max)	\
	((rand() % (int) ((Max) + 1) - (Min)) + (Min))


Person* RandomPersonData()
{
	char* FirstName[20] = { "Alex", "Ion", "Elena", "Cristina", "Maria",
							"George", "Paul", "Ioana", "Teodor", "Andreea",
							"Vasile", "Bogdan", "Cristian", "Daniel", "Madalina",
							"Ovidiu", "Catalina", "Robert", "Stefania", "Liviu" };
	
	char* LastName [20] = { "Popescu", "Pandele", "Badea", "Barbu", "Anton",
							"Grecu", "Ionescu", "Pintilie", "Hristache", "Nastase",
							"Morar", "Predoiu", "Pescaru", "Tataru", "Pana",
							"Ceapa", "Constantin", "Banu", "Ieremia", "Ciocan" };

	Person* person = malloc(sizeof(Person));

	strcpy(person->name, FirstName[RANDOM_NUMBER(0, 19)]);
	strcat(person->name, " ");
	strcat(person->name, LastName [RANDOM_NUMBER(0, 19)]);

	person->age = RANDOM_NUMBER(1, 99);

	return person;
}

Node* GeneratePersonList_DefaultPopulation()
{
	printf(" * Using default value for population count: %d\n\n", POPULATION);
	
	return GeneratePersonList(POPULATION, FALSE);
}

Node* GeneratePersonList(int _population, int bAllPersonsUnique)
{
	Person* firstPerson  = RandomPersonData();
	Node* personListHead = CreateNode(firstPerson);

	for (int i = 0; i < _population - 1; i++)
	{
		Person* newPerson = RandomPersonData();

		if (bAllPersonsUnique == TRUE)
			while (GetNodeWithValueIndex(personListHead, newPerson, PersonComparatorImpl) != -1)
				newPerson = RandomPersonData();

		AddNewNodeAtEnd(personListHead, newPerson, & PersonComparatorImpl);
	}

	return personListHead;
}

void PrintPersonList(Node* personListHead)
{
	Node* currentNode = personListHead;
	int counter = 1;

	while (currentNode)
	{
		Person* person = (Person *)currentNode->item;

		if (person->age == 1)
			printf("%d) %s - %d year old\n", counter ++, person->name, person->age);
		else
			printf("%d) %s - %d years old\n", counter ++, person->name, person->age);

		currentNode = currentNode->nextNode;
	}

	printf("--------------------------\n\n");
}

void PersonComparatorImpl(void* _person1, void* _person2, int* result)
{
	Person* p1 = (Person *) _person1;
	Person* p2 = (Person *) _person2;

	* result = 0;	// consider the items are different.
	
	if (strcmp(p1->name, p2->name) == 0 && p1->age == p2->age)
		* result = 1;
}

void PersonPrinterImpl(void* _person, int _posInList)
{
	Person* p = (Person *) _person;

	printf("      %d) %s is %d years old.", _posInList, p->name, p->age);
}
