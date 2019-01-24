#ifndef _STACK_H_
#include <stdio.h>

#define MAX_STACK_SIZE 1024
typedef struct _Element
{
	int nlcslen;
	int nrow;
	int ncolumn;
}Element;
typedef struct _Stack
{
	int top;
	Element data[MAX_STACK_SIZE];
}Stack;

bool Push(Stack *ps, Element *pein);
bool Pop(Stack *ps, Element *peout);
void InitialStack(Stack *ps);
bool GetTop(Stack *ps, Element *peout);
bool IsEmpty(Stack *ps);
bool IsFull(Stack *ps);
Element CreateElement(int nlen, int nrow, int ncol);

#define _STACK_H_
#endif