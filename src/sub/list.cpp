/* Linked List */

#include "list.h"

char* llist::FindSub(char* str, char* find)

{
	int i, j;
	for(i=j=0; *str; str++)
	{
		for(i=j=0; (*(str+i)==*(find+j))||(!*(find+j)); i++, j++)
		{
			if((*(str+i)==*(find+j)) && *(find+j))
				continue;
			if(!*(find+j))
			{
				char *found;
				found=((find+j)-strlen(find));
				return found;
			}
		}
	}
	return NULL;
}

le** llist::SearchList(char* keyw)
{
    // searches list for a variable
    le **results, **rp; // buffer for results
    le* c;
    results=(le**)malloc(GetElementsCount()+1);
    int i=GetElementsCount();
    for(c=start; c->next;)
    {
        int f=0;
        if(FindSub(c->itemdescrip, keyw)!=NULL)
            f++;
        if(FindSub(c->itemname, keyw)!=NULL)
            f++;
        if(f)
        {
           *rp=c;
           rp++;
        }
        c=c->next;
        if(!c)
            break;
    }
    return results;
}

bool llist::StepOne()
{
    le* tmp;        // pointer to le type
    tmp=cp->next;   // tmp = next of element pointed to by cp
    if(!tmp->next)
        return 0;
    cp=tmp;         // update cp
    return 1;
}

bool llist::UnstepOne()
{
    le* tmp;
    tmp=cp->last;
    if(!tmp)
        return 0;
    cp=tmp;
    return 1;
}

void llist::Clear(le *ptr, int size)
{
    char* cp;
    cp=(char*)ptr;
    for(int i=0; i<=size; i++, cp++)
    {
        *cp=0;
    }
}

void llist::InsertElement(le *insertafter)
{
    /* InsertElement */
    le *next;
    le *c;
    c=(le*)malloc(sizeof(le));
    Clear(c, sizeof(le));
    next=insertafter->next;
    insertafter->next=c;
    c->last=insertafter;
    c->next=next;
}

void llist::DeleteElement(le* element)
{
    /* DeleteElement : Deletes current element pointed to by cp */
    le *next;
    le *last;
    next=element->next;
    last=element->last;
    free(element);
    if(last && next) // item is not the first or last element
    {
        last->next=next;
        next->last=last;
        cp=last;
    }
    else if(!last && next) // item is the first element
    {
        next->last=NULL;
        cp=next;
        start=next;
    }
    else if(last && !next) // item is the last element
    {
        last->next=NULL;
        cp=last;
    }
    else if(!last && !next) // item is the only item!
    {
        cp=NULL;
        start=NULL;
    }
    return;
}


int llist::InitList(int nElements)
{
    le *ptr;
    le* prev;
    if(start)
        return 0; // failed because it was already initialized
    // otherwise, we continue.
    // first case is special
    start=ptr=(le*)malloc(sizeof(le));
    Clear(ptr, sizeof(le));
    cp=start;
    ptr->last=0; // ptr to last (none)
    prev=ptr;   // prev == current
    for(int i=0; i<(nElements-1); i++)
    {
        // this array creates array elements
        ptr=NULL;
        ptr=(le*)malloc(sizeof(le));
        Clear(ptr, sizeof(le));
        // **** ASSIGN CUSTOM INITIAL VALUES HERE
            ptr->id=(i+1);
        // **************************************
        ptr->last=prev;
        ptr->next=NULL;
        prev->next=ptr;
        prev=ptr;
    }
}

