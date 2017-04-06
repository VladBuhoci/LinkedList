#pragma once

#include "LinkedList.h"


typedef struct person_t
{
	char name[25];
	int age;
} Person;


/**
 * Generates a Person-type data structure with randomly picked values from a set of predefined options.
 * 
 * @return Returns a reference to the newly created Person structure.
 */
Person* RandomPersonData();

/**
 * Creates a new list of Person structures, with randomized values.
 * NOTE: Sometimes, a duplicate might be generated and thus not added to the list.
 * 
 * @return Returns a reference to the first node of this list.
 */
Node* GeneratePersonList_DefaultPopulation();

/**
 * Creates a new list of Person structures, with randomized values.
 * NOTE: Sometimes, a duplicate might be generated and thus not added to the list,
 * 		 if bAllPersonsUnique = FALSE.
 * 
 * @param _population 		 The number of people to create and store in a list.
 * @param _bAllPersonsUnique If TRUE, the generation process will test each new person to make sure
 *							 there will not be any duplicates present, at the end, in the list.
 * @return Returns a reference to the first node of this list.
 */
Node* GeneratePersonList(int _population, int bAllPersonsUnique);

/** Utility function to print the content of a list filled with Persons. */
void PrintPersonList(Node* personListHead);

/** Implementation for the list's comparator, to support Person-to-Person comparisons. */
void PersonComparatorImpl(void* _person1, void* _person2, int* result);

/** Implementation for the list's printer, to adjust the way Person data is shown. */
void PersonPrinterImpl(void* _person, int _posInList);

