#include "queue.h"

/* variables */
node_t* head;
node_t* tail;
int size;

void queueCreate()
{
	if (size != 0)
		queueClean();

	head = NULL;
	tail = NULL;
	size = 0;
}

void queueClean()
{
	while (size != 0)
		queuePop();
}

void queuePush(int val)
{
	node_t* newNode = (node_t*)malloc(sizeof(node_t));
	
	if (head == NULL)	// first node to enter to queue
		head = newNode;
	else
		tail->next = newNode;

	tail = newNode;
	newNode->next = NULL;
	newNode->value = val;
	++size;
}

int queuePop()
{
	if (head == NULL)
		return;

	node_t* pTemp = head;
	int temp = head->value;

	head = head->next;
	--size;
	free(pTemp);
	return temp;
}

int queueSize() { return size; }

int queuePeek() { return (head != NULL) ? head->value : NULL; }