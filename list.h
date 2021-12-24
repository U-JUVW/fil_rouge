#include "elt.h" 

#ifndef _LIST_H_
#define _LIST_H_

typedef struct node {
	_element data;
	struct node *pNext;
} _listNode, * _list;


_list addNode (_element e, _list n);
void showList(_list l);
int getLength(_list l);


#endif 


