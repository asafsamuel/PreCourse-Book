#pragma once
#ifndef _LIST_H_
#define _LIST_H_
#include "node.h"

/* Create a new list */
void listCreate();

/* Remove all list's nodes*/
void listRemoveAll();

/* Add new node to list */
void listAdd(int val);

/* Remove node from list */
void listRemove(node_t* pNode);

/* Get list's size (number of nodes) */
int listSize();

/* Get first node in the list */
node_t* listFirstNode();

/* Get last node in the list */
node_t* listLastNode();

/* Get avg node's values in the list */
float listAvgValues();

#endif // !_LIST_H_