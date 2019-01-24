#include "stack.h"

bool Push(Stack *ps, Element *pein)
{
	if(ps != NULL && pein != NULL)
	{
		if(IsFull(ps))
			return false;
		ps->top++;
		ps->data[ps->top].nlcslen = pein->nlcslen;
		ps->data[ps->top].nrow = pein->nrow;
		ps->data[ps->top].ncolumn = pein->ncolumn;
		return true;
	}
	return false;
}
bool Pop(Stack *ps, Element *peout)
{
	if(ps != NULL && peout != NULL)
	{
		if(IsEmpty(ps))
			return false;
		peout->nlcslen = ps->data[ps->top].nlcslen;
		peout->ncolumn = ps->data[ps->top].ncolumn;
		peout->nrow = ps->data[ps->top].nrow;
		ps->top--;
		return true;
	}
	return false;
}
void InitialStack(Stack *ps)
{
	if(ps!=NULL)
		ps->top = -1;
}
bool GetTop(Stack *ps, Element *peout)
{
	if(ps != NULL && peout != NULL)
	{
		if(ps->top >= 0)
		{
			peout->nlcslen = ps->data[ps->top].nlcslen;
			peout->ncolumn = ps->data[ps->top].ncolumn;
			peout->nrow = ps->data[ps->top].nrow;
			return true;
		}
	}
	return false;
}
bool IsEmpty(Stack *ps)
{
	if(ps != NULL)
		return (ps->top>=0)?false:true;
	return false;
}
bool IsFull(Stack *ps)
{
	if(ps != NULL)
		return (ps->top==MAX_STACK_SIZE)?true:false;
	return true;
}
Element CreateElement(int nlen, int nrow, int ncol)
{
	Element ele;
	ele.nlcslen = nlen;
	ele.ncolumn = ncol;
	ele.nrow = nrow;
	return ele;
}