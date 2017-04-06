#pragma once

#define TRUE	1
#define FALSE	0


typedef struct node_t
{
	void* item;
	struct node_t* nextNode;
} Node;


/**
 * Creates a new node and returns a reference.
 *
 * @param _item The item (value, pointer) this node will store.
 */
Node* CreateNode(void* _item);

/** Providing a list's head node, the function returns the size of that list. */
int ListLength(Node* listHeadNode);

/**
 * Prints the data in the list.
 * NOTE: Without providing a custom_printer() function, this will only print list indices and the pointer stored at each index.
 * 
 * @param bShowCount	 Prints the number of nodes in the list, before showing its actual content. Can be FALSE or TRUE
 * @param custom_printer Reference to a function that will be called for each item in this list. Can be NULL for lists with primitive values.
 */
void PrintList(Node* listHeadNode, int bShowCount, void custom_printer(void* _item, int pos));

/**
 * Returns the position of the node in the list or -1 if it couldn't be found.
 * 
 * @param comparator Reference to a function whose purpose is to check if _item1 and _item2 are equal or not.
 * @param comparator The pointer can be set to NULL, so no function will be called and items will compared in a default manner.
 * @param result Via this parameter, the comparator() function returns 0 if the two items are not equal and anything else if they are.
 */
int GetNodeIndex(Node* listHeadNode, Node* _nodeToFind, void comparator(void* _item1, void* _item2, int* result));

/**
 * Returns the position, in the list, of the node that contains the desired item or -1 if it couldn't be found.
 * 
 * @param comparator Reference to a function whose purpose is to check if _item1 and _item2 are equal or not.
 * @param comparator The pointer can be set to NULL, so no function will be called and items will compared in a default manner.
 * @param result Via this parameter, the comparator() function returns 0 if the two items are not equal and anything else if they are.
 */
int GetNodeWithValueIndex(Node* listHeadNode, void* _itemOfNodeToFind, void comparator(void* _item1, void* _item2, int* result));

/**
 * Adds a new node at the start of the list, containing the specified item and making it the new "first" node of that list.
 * 
 * @param comparator Check the GetNodeIndex() or GetNodeWithValueIndex() function for details about this.
 */
void AddNewNodeAtStart(Node** listHeadNode, void* _item, void comparator(void* _item1, void* _item2, int* result));

/**
 * Adds the provided node at the start of the list, making it the new "first" node of that list.
 * 
 * @param comparator Check the GetNodeIndex() or GetNodeWithValueIndex() function for details about this.
 */
void AddExistingNodeAtStart(Node** listHeadNode, Node* _nodeToAdd, void comparator(void* _item1, void* _item2, int* result));

/**
 * Adds a new node at the end of the list, containing the specified item.
 * 
 * @param comparator Check the GetNodeIndex() or GetNodeWithValueIndex() function for details about this.
 */
void AddNewNodeAtEnd(Node* listHeadNode, void* _item, void comparator(void* _item1, void* _item2, int* result));

/**
 * Adds the provided node at the end of the list.
 * 
 * @param comparator Check the GetNodeIndex() or GetNodeWithValueIndex() function for details about this.
 */
void AddExistingNodeAtEnd(Node* listHeadNode, Node* _nodeToAdd, void comparator(void* _item1, void* _item2, int* result));

/**
 * Removes the node at the specified index, from the list, if it is part of that list.
 * 
 * @return Returns the index of that node if it was successfully removed, or -1 in case of failure.
 */
int RemoveNodeByIndex(Node** listHeadNode, int _index);

/**
 * Removes the node containing the specified item, from the list, if it is part of that list.
 * 
 * @param comparator Check the GetNodeIndex() or GetNodeWithValueIndex() function for details about this.
 * @return Returns the index of that node if it was successfully removed, or -1 in case of failure.
 */
int RemoveNodeByValue(Node** listHeadNode, void* _item, void comparator(void* _item1, void* _item2, int* result));

/** Removes the first node from the list and returns 0 if successful or -1 if not. */
int RemoveFirstNode(Node** listHeadNode);

/** Removes the last node from the list and returns the index of that node if successful or -1 if not. */
int RemoveLastNode(Node* listHeadNode);

