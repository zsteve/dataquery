#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdlib.h>
#include <string.h>

typedef struct le{
    int id;
    char itemname[80];
    char itemdescrip[80];
    le *last;
    le *next;
};

class llist{
    // list object class
    le *start; // pointer to start of linked list
    le  *cp;    // pointer to current element
    public:
    // public elements of list

    // inline functions
    le *GetStart(){return start;}
    le *GetCP(){return cp;}
    void SetCP(le *n){cp=n;}
    int GetElementsCount()
    {
        int i;
        le* c=start;
        for(i=0; ;)
        {
            i++;
            if(!c->next)
                break;
            c=c->next;
        }
        return i;
    }
    // member function prototypes
    bool StepOne();
    bool UnstepOne();
    void Clear(le* ptr, int size);
    int InitList(int nElements);
    bool DestroyList();
    void CatElement(int nw);
    void InsertElement(le *insertafter);
    void DeleteElement(le *element);
    char* FindSub(char* str, char* find);
    le** SearchList(char* keyw);

    // constructor
    llist(){
        start=cp=0;
    }
};


#endif // LIST_H_INCLUDED
