#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Person.h"
#include "LinkedList.h"

#define DEFAULT_POPULATION 10

#define RANDOM_NUMBER(Min, Max)	\
	((rand() % (int) ((Max) + 1) - (Min)) + (Min))


Person* random_person_data()
{
	char* first_name[20] = { "Alex", "Ion", "Elena", "Cristina", "Maria",
							 "George", "Paul", "Ioana", "Teodor", "Andreea",
							 "Vasile", "Bogdan", "Cristian", "Daniel", "Madalina",
							 "Ovidiu", "Catalina", "Robert", "Stefania", "Liviu" };
	
	char* last_name [20] = { "Popescu", "Pandele", "Badea", "Barbu", "Anton",
							 "Grecu", "Ionescu", "Pintilie", "Hristache", "Nastase",
							 "Morar", "Predoiu", "Pescaru", "Tataru", "Pana",
							 "Ceapa", "Constantin", "Banu", "Ieremia", "Ciocan" };

	Person* person = malloc(sizeof(Person));
	if (person) {
		strcpy(person->name, first_name[RANDOM_NUMBER(0, 19)]);
		strcat(person->name, " ");
		strcat(person->name, last_name[RANDOM_NUMBER(0, 19)]);
		
		person->age = RANDOM_NUMBER(1, 99);
	}

	return person;
}

Node* generate_person_list_default()
{
	printf(" * Using default value for population count: %d\n\n", DEFAULT_POPULATION);
	
	return generate_person_list(DEFAULT_POPULATION, TRUE);
}

Node* generate_person_list(int population, int all_persons_unique)
{
	Person* first_person;
	Node* person_list_head;

	first_person = random_person_data();
	if (first_person == NULL)
		return NULL;

	person_list_head = create_node(first_person);

	for (int i = 0; i < population - 1; i++) {
		Person* new_person = random_person_data();
		if (new_person == NULL)
			break;

		if (all_persons_unique == TRUE)
			while (get_node_with_value_index(person_list_head, new_person, person_comparator_impl) != -1)
				new_person = random_person_data();

		add_new_node_at_end(person_list_head, new_person, & person_comparator_impl);
	}

	return person_list_head;
}

void print_person_list(Node* person_list_head)
{
	Node* current_node = person_list_head;
	int counter = 1;

	while (current_node)	{
		Person* person = (Person *) current_node->item;

		if (person->age == 1)
			printf("%d) %s - %d year old\n", counter ++, person->name, person->age);
		else
			printf("%d) %s - %d years old\n", counter ++, person->name, person->age);

		current_node = current_node->next_node;
	}

	printf("--------------------------\n\n");
}

void person_comparator_impl(void* person1, void* person2, int* result)
{
	Person* p1 = (Person *) person1;
	Person* p2 = (Person *) person2;

	*result = 0;	/* consider the items are different. */
	
	if (strcmp(p1->name, p2->name) == 0 && p1->age == p2->age)
		*result = 1;
}

void person_printer_impl(void* person, int pos_in_list)
{
	Person* p = (Person *) person;

	printf("      %d) %s is %d years old.", pos_in_list, p->name, p->age);
}

void person_removal_impl(void* person)
{
	free(person);
}

