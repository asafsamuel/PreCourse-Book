#include "Stack.h"

Stack* initStack(unsigned int capacity)
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->capacity = capacity;
	stack->top = -1;
	stack->arr = (int*)malloc(sizeof(int)*capacity);
	return stack;
}

void push(Stack* s, int val)
{
	if (isFull(s))
		return;
	s->arr[s->top] = val;
	s->top++;
}

int pop(Stack* s)
{
	if (isEmpty(s))
		return INT_MIN;
	s->top--;
	return s->arr[s->top];
}

int isEmpty(Stack* s)
{
	return s->top == -1;
}

int isFull(Stack* s)
{
	return s->top == s->capacity - 1;
}