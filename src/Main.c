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
void custom_integer_printer(void* number, int pos_in_list)
{
	printf("      {index %d with value = %d}", pos_in_list, (int) (intptr_t) number);
}

/** Application entry point. */
int main(int argc, char* argv[])
{
	/* We can still make a list with primitive values, after the changes done to the list, although we need to cast to (void *). */
	/* Uncomment to test this. */
	/*
	Node* list_head_node = NULL;
	print_list(list_head_node, TRUE, NULL);

	list_head_node = create_node((void *)12);
	print_list(list_head_node, TRUE, NULL);

	Node* next_node = create_node((void *)-2);
	list_head_node->next_node = next_node;
	print_list(list_head_node, FALSE, custom_integer_printer);

	add_new_node_at_start(& list_head_node, (void *)3, NULL);
	print_list(list_head_node, TRUE, custom_integer_printer);

	Node* test_node = create_node((void *)-17);
	add_existing_node_at_start(&list_head_node, test_node, NULL);
	print_list(list_head_node, FALSE, NULL);

	// Test if we can create and add a node with a certain value to a list,
	// when the list already contains a node which stores that value. (result: nothing happens)
	add_new_node_at_start(& list_head_node, (void *)3, NULL);
	print_list(list_head_node, FALSE, custom_integer_printer);

	// Test if we can add a node which is already part of this list. (result: nothing happens)
	add_existing_node_at_start(& list_head_node, next_node, NULL);
	print_list(list_head_node, TRUE, custom_integer_printer);

	add_new_node_at_end(list_head_node, (void *)45, NULL);
	print_list(list_head_node, TRUE, NULL);

	Node* testNode2 = create_node((void *)-18);
	add_existing_node_at_end(list_head_node, testNode2, NULL);
	print_list(list_head_node, TRUE, custom_integer_printer);

	remove_node_by_index(& list_head_node, 4, NULL);		// 4 is an index here.
	print_list(list_head_node, FALSE, custom_integer_printer);

	remove_node_by_value(& list_head_node, (void *)12, NULL, NULL);
	print_list(list_head_node, TRUE, NULL);

	remove_first_node(& list_head_node, NULL);
	print_list(list_head_node, TRUE, NULL);

	add_new_node_at_start(& list_head_node, (void *)314, NULL);
	print_list(list_head_node, TRUE, NULL);

	remove_last_node(list_head_node, NULL);
	print_list(list_head_node, TRUE, custom_integer_printer);
	*/
	
	Node* person_list_head;
	int population;

	srand(time(NULL));

	if (argc > 1)
		population = atoi(argv[1]);
	else {
		printf(" ~ Number of persons to generate: ");
		scanf("%d", &population); getchar();
		printf("\n");
	}

	if (population > 0)
		person_list_head = generate_person_list(population, TRUE);
	else
		person_list_head = generate_person_list_default();

	/* If population list creation was successful, perform a few tests. */
	if (person_list_head) {
		/* Output the list's content. */
		print_person_list(person_list_head);

		/* Manually adding people to the list, using the structure itself. */
		Person* another_person = malloc(sizeof(Person));
		if (another_person) {
			strcpy(another_person->name, "Vlad Buhoci");
			another_person->age = 21;

			add_new_node_at_start(&person_list_head, another_person, person_comparator_impl);
		}

		/* Checking if the list accepts duplicates. (it doesn't) */
		Person* another_person_2 = malloc(sizeof(Person));
		if (another_person_2) {
			strcpy(another_person_2->name, "Vlad Buhoci");
			another_person_2->age = 21;

			add_new_node_at_end(person_list_head, another_person_2, person_comparator_impl);
		}

		/* Show the content of the new list, after changes (both functions work): */
		//print_person_list(person_list_head);						/* Custom Person printer function. */

		print_list(person_list_head, FALSE, person_printer_impl);	/* List's printer function, with custom Person printing helper function. */

		remove_node_by_index(&person_list_head, 3, person_removal_impl);
		remove_first_node(&person_list_head, person_removal_impl);
		print_list(person_list_head, TRUE, person_printer_impl);
	}
	else {
		printf("Failed to generate a list of persons.\n");

		getchar();
		return EXIT_FAILURE;
	}

	getchar();
	return EXIT_SUCCESS;
}
