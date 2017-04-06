#pragma once

#define TRUE	1
#define FALSE	0


typedef struct node_t
{
	void* item;
	struct node_t* next_node;
} Node;


/**
 * Creates a new node and returns a reference.
 * NOTE: this can return NULL, so always check the returned pointer before using it.
 *
 * @param item The item (value, pointer) this node will store.
 */
Node* create_node(void* item);

/** Providing a list's head node, the function returns the size of that list. */
int list_length(Node* list_head_node);

/**
 * Prints the data in the list.
 * NOTE: Without providing a custom_printer() function, this will only print list indices and the pointer stored at each index.
 * 
 * @param show_count	 Prints the number of nodes in the list, before showing its actual content. Can be FALSE or TRUE.
 * @param custom_printer Reference to a function that will be called for each item in this list. Can be NULL for lists with primitive values.
 */
void print_list(Node* list_head_node, int show_count, void custom_printer(void* item, int pos));

/**
 * Returns the position of the node in the list or -1 if it couldn't be found.
 * 
 * @param comparator Reference to a function whose purpose is to check if _item1 and _item2 are equal or not.
 *					 The pointer can be set to NULL, so no function will be called and items will compared in a default manner.
 * @param result Via this parameter, the comparator() function returns 0 if the two items are not equal and anything else if they are.
 */
int get_node_index(Node* list_head_node, Node* node_to_find, void comparator(void* item1, void* item2, int* result));

/**
 * Returns the position, in the list, of the node that contains the desired item or -1 if it couldn't be found.
 * 
 * @param comparator Reference to a function whose purpose is to check if _item1 and _item2 are equal or not.
 *					 The pointer can be set to NULL, so no function will be called and items will compared in a default manner.
 * @param result Via this parameter, the comparator() function returns 0 if the two items are not equal and anything else if they are.
 */
int get_node_with_value_index(Node* list_head_node, void* item_of_node_to_find, void comparator(void* item1, void* item2, int* result));

/**
 * Adds a new node at the start of the list, containing the specified item and making it the new "first" node of that list.
 * 
 * @param comparator Check the get_node_index() or get_node_with_value_index() function for details about this.
 */
void add_new_node_at_start(Node** list_head_node, void* item, void comparator(void* item1, void* item2, int* result));

/**
 * Adds the provided node at the start of the list, making it the new "first" node of that list.
 * 
 * @param comparator Check the get_node_index() or get_node_with_value_index() function for details about this.
 */
void add_existing_node_at_start(Node** list_head_node, Node* node_to_add, void comparator(void* item1, void* item2, int* result));

/**
 * Adds a new node at the end of the list, containing the specified item.
 * 
 * @param comparator Check the get_node_index() or get_node_with_value_index() function for details about this.
 */
void add_new_node_at_end(Node* list_head_node, void* item, void comparator(void* item1, void* item2, int* result));

/**
 * Adds the provided node at the end of the list.
 * 
 * @param comparator Check the get_node_index() or get_node_with_value_index() function for details about this.
 */
void add_existing_node_at_end(Node* list_head_node, Node* node_to_add, void comparator(void* item1, void* item2, int* result));

/**
 * Removes the node at the specified index, from the list, if it is part of that list.
 * 
 * @param custom_free Can be NULL for lists with primitive type values.
					  Implementations should deal with freeing resources according to the structure of the items added to the list.
 * @return Returns the index of that node if it was successfully removed, or -1 in case of failure.
 */
int remove_node_by_index(Node** list_head_node, int index, void custom_free(void* item));

/**
 * Removes the node containing the specified item, from the list, if it is part of that list.
 * 
 * @param custom_free Can be NULL for lists with primitive type values.
					  Implementations should deal with freeing resources according to the structure of the items added in the list.
 * @param comparator Check the get_node_index() or get_node_with_value_index() function for details about this.
 * @return Returns the index of that node if it was successfully removed, or -1 in case of failure.
 */
int remove_node_by_value(Node** list_head_node, void* item, void custom_free(void* item), void comparator(void* item1, void* item2, int* result));

/**
 * Removes the first node from the list and returns 0 if successful or -1 if not.
 * 
 * @param custom_free Can be NULL for lists with primitive type values.
					  Implementations should deal with freeing resources according to the structure of the items added in the list.
 */
int remove_first_node(Node** list_head_node, void custom_free(void* item));

/**
 * Removes the last node from the list and returns the index of that node if successful or -1 if not.
 * 
 * @param custom_free Can be NULL for lists with primitive type values.
					  Implementations should deal with freeing resources according to the structure of the items added in the list.
 */
int remove_last_node(Node* list_head_node, void custom_free(void* item));

