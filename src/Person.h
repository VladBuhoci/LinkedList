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
Person* random_person_data();

/**
 * Creates a new list of Person structures, with randomized values.
 * NOTE: This will never add duplicates to the list, by default.
 * 
 * @return Returns a reference to the first node of this list.
 */
Node* generate_person_list_default();

/**
 * Creates a new list of Person structures, with randomized values.
 * NOTE: Sometimes, a duplicate might be generated and thus not added to the list,
 * 		 if bAllPersonsUnique = FALSE.
 * 
 * @param population 		 The number of people to create and store in a list.
 * @param all_persons_unique If TRUE, the generation process will test each new person to make sure
 *							 there will not be any duplicates present, at the end, in the list.
 * @return Returns a reference to the first node of this list.
 */
Node* generate_person_list(int population, int all_persons_unique);

/** Utility function to print the content of a list filled with Persons. */
void print_person_list(Node* person_list_head);

/** Implementation for the list's comparator, to support Person-to-Person comparisons. */
void person_comparator_impl(void* person1, void* person2, int* result);

/** Implementation for the list's printer, to adjust the way Person data is shown. */
void person_printer_impl(void* person, int pos_in_list);

/** Implementation for the list's removal functions, making sure resources are freed correctly. */
void person_removal_impl(void* person);

