#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"


Node* create_node(void* item)
{
	Node* new_node = malloc(sizeof(Node));
	if (new_node) {
		new_node->item = item;
		new_node->next_node = NULL;
	}

	return new_node;
}

int list_length(Node* list_head_node)
{
	Node* node = list_head_node;
	int size = 0;

	while (node) {
		size += 1;
		node = node->next_node;
	}

	return size;
}

void print_list(Node* list_head_node, int show_count, void custom_printer(void* item, int pos))
{
	Node* node = list_head_node;
	int counter = 0;

	if (show_count == TRUE)
		printf(" ~ List of size %d with the following content:\n", list_length(list_head_node));
	else
		printf(" ~ List with the following content:\n");

	printf("    [\n");

	while (node) {
		if (custom_printer)
			custom_printer(node->item, counter + 1);
		else
			printf("      (node %d, value = %p)", counter, node->item);

		printf("\n");

		node = node->next_node;
		counter += 1;
	}

	printf("    ]\n--------------------------\n\n");
}

int get_node_index(Node* list_head_node, Node* node_to_find, void comparator(void* item1, void* item2, int* result))
{
	Node* current_node = list_head_node;
	int counter = 0;

	while (current_node) {
		if (comparator) {
			int result;
			comparator(current_node->item, node_to_find->item, & result);

			/* 0 means FALSE, anything else means TRUE. */
			if (result != 0)
				return counter;
		} else if (current_node->item == node_to_find->item)
			return counter;

		current_node = current_node->next_node;
		counter += 1;
	}

	return -1;	/* if the node wasn't found, return -1. */
}

int get_node_with_value_index(Node* list_head_node, void* item_of_node_to_find, void comparator(void* item1, void* item2, int* result))
{
	Node* current_node = list_head_node;
	int counter = 0;

	while (current_node) {
		if (comparator) {
			int result;
			comparator(current_node->item, item_of_node_to_find, & result);

			/* 0 means FALSE, anything else means TRUE. */
			if (result != 0)
				return counter;
		} else if (current_node->item == item_of_node_to_find)
			return counter;

		current_node = current_node->next_node;
		counter += 1;
	}

	return -1;	/* if the node wasn't found, return -1. */
}

void add_new_node_at_start(Node** list_head_node, void* item, void comparator(void* item1, void* item2, int* result))
{
	/* If the list already has a node containing that value, exit from this function. */
	if (get_node_with_value_index(* list_head_node, item, comparator) != -1)
		return;

	Node* new_node = malloc(sizeof(Node));
	if (new_node) {
		new_node->item = item;
		new_node->next_node = *list_head_node;

		*list_head_node = new_node;
	}
}

void add_existing_node_at_start(Node** list_head_node, Node* node_to_add, void comparator(void* item1, void* item2, int* result))
{
	/* If the node already exists within this list, exit from this function. */
	if (get_node_index(* list_head_node, node_to_add, comparator) != -1)
		return;

	node_to_add->next_node = * list_head_node;
	*list_head_node = node_to_add;
}

void add_new_node_at_end(Node* list_head_node, void* item, void comparator(void* item1, void* item2, int* result))
{
	/* If the list already has a node containing that value, exit from this function. */
	if (get_node_with_value_index(list_head_node, item, comparator) != -1)
		return;

	Node* current_node = list_head_node;

	while (current_node->next_node)
		current_node = current_node->next_node;

	current_node->next_node = create_node(item);
}

void add_existing_node_at_end(Node* list_head_node, Node* node_to_add, void comparator(void* item1, void* item2, int* result))
{
	/* If the node already exists within this list, exit from this function. */
	if (get_node_index(list_head_node, node_to_add, comparator) != -1)
		return;

	Node* current_node = list_head_node;

	while (current_node->next_node)
		current_node = current_node->next_node;

	current_node->next_node = node_to_add;
}

int remove_node_by_index(Node** list_head_node, int index, void custom_free(void* item))
{
	if (index < 0 || index > list_length(* list_head_node) - 1)
		return -1;

	if (index == 0)
		return remove_first_node(list_head_node, custom_free);

	if (index == list_length(* list_head_node) - 1)
		return remove_last_node(* list_head_node, custom_free);

	/* Else, save the last node that sits right before the one we want removed. */
	
	Node* current_node = *list_head_node;

	for (int i = 1; i < index; i ++)
		current_node = current_node->next_node;

	Node* temp_node = current_node->next_node;
	current_node->next_node = current_node->next_node->next_node;

	if (custom_free)
		custom_free(temp_node->item);
	free(temp_node);

	return index;
}

int remove_node_by_value(Node** list_head_node, void* item, void custom_free(void* item), void comparator(void* item1, void* item2, int* result))
{
	if ((* list_head_node)->item == item)
		return remove_first_node(list_head_node, custom_free);

	int position = get_node_with_value_index(* list_head_node, item, comparator);

	if (position == -1)
		return -1;

	/* Save the last node that sits right before the one we want removed. */

	Node* current_node = *list_head_node;
	
	for (int index = 1; index < position; index ++)
		current_node = current_node->next_node;

	Node* temp_node = current_node->next_node;
	current_node->next_node = current_node->next_node->next_node;

	if (custom_free)
		custom_free(temp_node->item);
	free(temp_node);

	return position;
}

int remove_first_node(Node** list_head_node, void custom_free(void* item))
{
	if ((* list_head_node) == NULL)
		return -1;

	/* Else... (if the first node exists) */

	Node* new_head_node = (* list_head_node)->next_node;

	if (custom_free)
		custom_free((*list_head_node)->item);
	free(* list_head_node);
	
	*list_head_node = new_head_node;

	return 0;
}

int remove_last_node(Node* list_head_node, void custom_free(void* item))
{
	if (list_head_node == NULL)
		return -1;

	if (list_head_node->next_node == NULL)		/* if the list has only one node, call the corresponding removal function. */
		return remove_first_node(& list_head_node, custom_free);

	/* Else... */

	Node* current_node = list_head_node;
	int index = 1;

	while (current_node->next_node) {
		current_node = current_node->next_node;
		index += 1;

		if (current_node->next_node->next_node == NULL) {
			if (custom_free)
				custom_free(current_node->next_node->item);
			free(current_node->next_node);

			current_node->next_node = NULL;

			break;
		}
	}

	return index;
}

