#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "LinkedList.h"
#include "Person.h"
#include <stdint.h>


/**
 * Implementation for the list's printer function, suggesting
 * the way lists of integers should be printed.
 */
void CustomIntegerPrinter(void* _number, int _posInList)
{
	printf("      {index %d with value = %d}", _posInList, (int) (intptr_t) _number);
}

/**
 * Main.
 */
int main()
{
	// We can still make a list with primitive values, after the changes done to the list,
	// although we need to cast to void*.
	/*
	Node* ListHeadNode = NULL;
	PrintList(ListHeadNode, TRUE, NULL);

	ListHeadNode = CreateNode((void *) 12);
	PrintList(ListHeadNode, TRUE, NULL);

	Node* nextNode = CreateNode((void *) -2);
	ListHeadNode->nextNode = nextNode;
	PrintList(ListHeadNode, FALSE, CustomIntegerPrinter);

	AddNewNodeAtStart(& ListHeadNode, (void *) 3, NULL);
	PrintList(ListHeadNode, TRUE, CustomIntegerPrinter);

	Node* testNode = CreateNode((void *) -17);
	AddExistingNodeAtStart(& ListHeadNode, testNode, NULL);
	PrintList(ListHeadNode, FALSE, NULL);

	// Test if we can create and add a node with a certain value to a list,
	// when the list already contains a node which stores that value. (result: nothing happens)
	AddNewNodeAtStart(& ListHeadNode, (void *) 3, NULL);
	PrintList(ListHeadNode, FALSE, CustomIntegerPrinter);

	// Test if we can add a node which is already part of this list. (result: nothing happens)
	AddExistingNodeAtStart(& ListHeadNode, nextNode, NULL);
	PrintList(ListHeadNode, TRUE, CustomIntegerPrinter);

	AddNewNodeAtEnd(ListHeadNode, (void *) 45, NULL);
	PrintList(ListHeadNode, TRUE, NULL);

	Node* testNode2 = CreateNode((void *) -18);
	AddExistingNodeAtEnd(ListHeadNode, testNode2, NULL);
	PrintList(ListHeadNode, TRUE, CustomIntegerPrinter);

	RemoveNodeByIndex(& ListHeadNode, 4);		// 4 is an index here.
	PrintList(ListHeadNode, FALSE, CustomIntegerPrinter);

	RemoveNodeByValue(& ListHeadNode, (void *) 12, NULL);
	PrintList(ListHeadNode, TRUE, NULL);

	RemoveFirstNode(& ListHeadNode);
	PrintList(ListHeadNode, TRUE, NULL);

	AddNewNodeAtStart(& ListHeadNode, (void *) 314, NULL);
	PrintList(ListHeadNode, TRUE, NULL);

	RemoveLastNode(ListHeadNode);
	PrintList(ListHeadNode, TRUE, CustomIntegerPrinter);
	*/

	int population;

	printf(" ~ Number of persons to generate: ");
	scanf("%d", & population); getchar();
	printf("\n");
	
	srand(time(NULL));

	Node* PersonListHead;
	
	if (population > 0)
		PersonListHead = GeneratePersonList(population, TRUE);
	else
		PersonListHead = GeneratePersonList_DefaultPopulation();

	// Output the list.
	PrintPersonList(PersonListHead);

	// Manually adding people to the list, with the structure itself.
	Person* anotherPerson = malloc(sizeof(Person));
	strcpy(anotherPerson->name, "Vlad Buhoci");
	anotherPerson->age  = 21;

	AddNewNodeAtStart(& PersonListHead, anotherPerson, PersonComparatorImpl);

	// Manually adding people to the list, using a function.
	AddNewNodeAtEnd(PersonListHead, RandomPersonData(), PersonComparatorImpl);

	// Checking if the list accepts duplicates. (it doesn't)
	Person* anotherPerson2 = malloc(sizeof(Person));
	strcpy(anotherPerson2->name, "Vlad Buhoci");
	anotherPerson2->age = 21;

	AddNewNodeAtEnd(PersonListHead, anotherPerson2, PersonComparatorImpl);
	
	// Show the content of the new list, after changes:
	// (both functions work)

	//PrintPersonList(PersonListHead);						// Custom Person printer function.

	PrintList(PersonListHead, FALSE, PersonPrinterImpl);	// List's printer function, with custom Person printing helper function.

	getchar();
	return 0;
}
