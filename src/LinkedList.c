#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"


Node* CreateNode(void* _item)
{
	Node* newNode = malloc(sizeof(Node));
	newNode->item = _item;
	newNode->nextNode = NULL;

	return newNode;
}

int ListLength(Node* listHeadNode)
{
	Node* node = listHeadNode;
	int size = 0;

	while (node)
	{
		size += 1;
		node = node->nextNode;
	}

	return size;
}

void PrintList(Node* listHeadNode, int bShowCount, void custom_printer(void* _item, int pos))
{
	Node* node = listHeadNode;
	int counter = 0;

	if (bShowCount == TRUE)
		printf(" ~ List of size %d with the following content:\n", ListLength(listHeadNode));
	else
		printf(" ~ List with the following content:\n");

	printf("    [\n");

	while (node)
	{
		if (custom_printer != NULL)
			custom_printer(node->item, counter + 1);
		else
			printf("      (node %d, value = %p)", counter, node->item);

		printf("\n");

		node = node->nextNode;
		counter += 1;
	}

	printf("    ]\n--------------------------\n\n");
}

int GetNodeIndex(Node* listHeadNode, Node* _nodeToFind, void comparator(void* _item1, void* _item2, int* result))
{
	Node* currentNode = listHeadNode;
	int counter = 0;

	while (currentNode)
	{
		if (comparator != NULL)
		{
			int result;
			comparator(currentNode->item, _nodeToFind->item, & result);

			// 0 means FALSE, anything else means TRUE.
			if (result != 0)
				return counter;
		}
		else if (currentNode->item == _nodeToFind->item)
			return counter;

		currentNode = currentNode->nextNode;
		counter += 1;
	}

	return -1;	// if the node wasn't found, return -1.
}

int GetNodeWithValueIndex(Node* listHeadNode, void* _itemOfNodeToFind, void comparator(void* _item1, void* _item2, int* result))
{
	Node* currentNode = listHeadNode;
	int counter = 0;

	while (currentNode)
	{
		if (comparator != NULL)
		{
			int result;
			comparator(currentNode->item, _itemOfNodeToFind, & result);

			// 0 means FALSE, anything else means TRUE.
			if (result != 0)
				return counter;
		}
		else if (currentNode->item == _itemOfNodeToFind)
			return counter;

		currentNode = currentNode->nextNode;
		counter += 1;
	}

	return -1;	// if the node wasn't found, return -1.
}

void AddNewNodeAtStart(Node** listHeadNode, void* _item, void comparator(void* _item1, void* _item2, int* result))
{
	// If the list already has a node containing that value, exit from this function.
	if (GetNodeWithValueIndex(* listHeadNode, _item, comparator) != -1)
		return;

	Node* newNode = malloc(sizeof(Node));

	newNode->item     = _item;
	newNode->nextNode = * listHeadNode;

	* listHeadNode = newNode;
}

void AddExistingNodeAtStart(Node** listHeadNode, Node* _nodeToAdd, void comparator(void* _item1, void* _item2, int* result))
{
	// If the node already exists within this list, exit from this function.
	if (GetNodeIndex(* listHeadNode, _nodeToAdd, comparator) != -1)
		return;

	_nodeToAdd->nextNode = * listHeadNode;

	* listHeadNode = _nodeToAdd;
}

void AddNewNodeAtEnd(Node* listHeadNode, void* _item, void comparator(void* _item1, void* _item2, int* result))
{
	// If the list already has a node containing that value, exit from this function.
	if (GetNodeWithValueIndex(listHeadNode, _item, comparator) != -1)
		return;

	Node* currentNode = listHeadNode;

	while (currentNode->nextNode)
		currentNode = currentNode->nextNode;

	currentNode->nextNode = CreateNode(_item);
}

void AddExistingNodeAtEnd(Node* listHeadNode, Node * _nodeToAdd, void comparator(void* _item1, void* _item2, int* result))
{
	// If the node already exists within this list, exit from this function.
	if (GetNodeIndex(listHeadNode, _nodeToAdd, comparator) != -1)
		return;

	Node* currentNode = listHeadNode;

	while (currentNode->nextNode)
		currentNode = currentNode->nextNode;

	currentNode->nextNode = _nodeToAdd;
}

int RemoveNodeByIndex(Node** listHeadNode, int _index)
{
	if (_index < 0 || _index > ListLength(* listHeadNode) - 1)
		return -1;

	if (_index == 0)
		return RemoveFirstNode(listHeadNode);

	if (_index == ListLength(* listHeadNode) - 1)
		return RemoveLastNode(* listHeadNode);

	// Else...
	
	Node* currentNode = * listHeadNode;

	// Save the last node that sits right before the one we want removed.
	for (int index = 1; index < _index; index ++)
	{
		currentNode = currentNode->nextNode;
	}

	Node* tempNode		  = currentNode->nextNode;
	currentNode->nextNode = currentNode->nextNode->nextNode;

	free(tempNode);

	return _index;
}

int RemoveNodeByValue(Node** listHeadNode, void* _item, void comparator(void* _item1, void* _item2, int* result))
{
	if ((* listHeadNode)->item == _item)
		return RemoveFirstNode(listHeadNode);

	int position = GetNodeWithValueIndex(* listHeadNode, _item, comparator);

	if (position == -1)
		return -1;

	Node* currentNode = * listHeadNode;

	// Save the last node that sits right before the one we want removed.
	for (int index = 1; index < position; index ++)
	{
		currentNode = currentNode->nextNode;
	}

	Node* tempNode = currentNode->nextNode;
	currentNode->nextNode = currentNode->nextNode->nextNode;

	free(tempNode);

	return position;
}

int RemoveFirstNode(Node** listHeadNode)
{
	if ((* listHeadNode) == NULL)
		return -1;

	// Else... (if the first node exists)

	Node* newHeadNode = (* listHeadNode)->nextNode;
	
	free(* listHeadNode);

	* listHeadNode = newHeadNode;

	return 0;
}

int RemoveLastNode(Node* listHeadNode)
{
	if (listHeadNode == NULL)
		return -1;

	if (listHeadNode->nextNode == NULL)		// if the list has only one node, call the corresponding removal function.
		return RemoveFirstNode(& listHeadNode);

	// Else...

	Node* currentNode = listHeadNode;
	int index = 1;

	while (currentNode->nextNode)
	{
		currentNode = currentNode->nextNode;
		index += 1;

		if (currentNode->nextNode->nextNode == NULL)
		{
			free(currentNode->nextNode);
			
			currentNode->nextNode = NULL;

			break;
		}
	}

	return index;
}

