#pragma once
#ifndef _STACK_H_
#define _STACK_H_

#include <malloc.h>
#include <stdlib.h> 

typedef struct
{
	unsigned capacity;
	int top;
	int* arr;
}Stack;

Stack* initStack(unsigned int capacity);
void push(Stack* s, int val);
int pop(Stack* s);

int isFull(Stack* s);
int isEmpty(Stack* s);

#endif // !_STACK_H_
