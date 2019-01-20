#pragma once
#ifndef _NODE_H_
#define _NODE_H_
#include <stdlib.h>

/* Struct declaration */
typedef struct node_t node_t;
typedef struct node_t
{
	node_t* next;
	node_t* prev;
	int value;
}node_t;

/* Get next node */
inline node_t* nextNode(node_t* currNode) { return (currNode != NULL) ? currNode->next : NULL; }

/* Get previus node */
inline node_t* prevNode(node_t* currNode) { return (currNode != NULL) ? currNode->prev : NULL; }

/* Get node's value */
inline int value(node_t* pNode) { return (pNode != NULL) ? pNode->value : 0; }

#endif // !_NODE_H_