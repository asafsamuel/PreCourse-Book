#pragma once
#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "node.h"

/* Create new queue */
void queueCreate();

/* Remove all queue's nodes */
void queueClean();

/* Add new node to the end of the queue */
void queuePush(int val);

/* Pop first value from the queue */
int queuePop();

/* Get queue's size */
int queueSize();

/* Peek first value in the queue */
int queuePeek();

#endif // !_QUEUE_H_