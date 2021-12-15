#include "elt.h" 

#ifndef _LIST_H_
#define _LIST_H_

typedef struct node {
	_element data;
	struct node *pNext;
} _listNode, * _list;

_listNode * addNode (_element e, _listNode * n);
void showList(_list l);
void freeList(_list l);
_element getFirstElt(_list l);
_list removeFirstNode(_list l);
void showList_rec(_list l);
void showList_inv_rec(_list l);
void freeList_rec(_list l);


#endif 


