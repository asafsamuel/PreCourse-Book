#include "list.h"

/* variables */
node_t* head;
node_t* last;
int size;
float avg;

void listCreate()
{
	if (size != 0)
		listRemoveAll();

	head = NULL;
	last = NULL;
	size = 0;
	avg = 0;
}

void listRemoveAll()
{
	while (head != NULL)
		listRemove(head);
}

void listAdd(int val)
{
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	if (newNode == NULL)
		return;

	if (head == NULL)	// first node to add
	{
		head = newNode;
		newNode->prev = NULL;
	}

	else
	{
		newNode->prev = last;
		last->next = newNode;
	}

	last = newNode;
	newNode->value = val;
	newNode->next = NULL;
	avg = (avg*(size - 1) + val) / (++size);
}

void listRemove(node_t* pNode)
{
	if (pNode == NULL)
		return;

	if (pNode == head)	// remove head
	{
		head = pNode->next;
		if (head != NULL)
			head->prev = NULL;
	}

	else if (pNode == last) // remove last
	{
		last = pNode->prev;
		last->next = NULL;
	}

	else
	{
		(*pNode->prev).next = pNode->next;
		(*pNode->next).prev = pNode->prev;
	}

	avg = (avg*(size + 1) - (float)pNode->value) / (--size);
	avg = (size == 0) ? 0 : avg;
	free(pNode);
}

int listSize() { return size; }

node_t* listFirstNode() { return head; }

node_t* listLastNode() { return last; }

float listAvgValues() { return avg; }