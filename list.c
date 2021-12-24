#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "elt.h" // _element 
#include "list.h" // prototypes 

static _listNode * newNode(_element e) {
	// Créer une nouvelle cellule contenant l'élément e

	_listNode * pNode; 
	pNode = malloc(sizeof(_listNode));
	assert(pNode != NULL);
	pNode->data = e; 
	pNode->pNext = NULL;

	return pNode;
}

_listNode * addNode (_element e, _listNode * n) {
	// Créer une maille (node), la remplir 
	// et l'accrocher en tête d'une liste existante (ou vide)
	// Renvoyer la nouvelle tête
	_listNode * pNode; 
	
	pNode = newNode(e); 
	pNode->pNext = n; 
	return pNode;
}

int getLength(_list l){
	int length = 0;
	while(l != NULL){
		length ++;
		l = l->pNext;
	}
	return length;
}

void showList(_list l) {
	// Afficher la liste en commençant par sa tête 
	// A faire en itératif 

	if (l==NULL) {
		printf("Liste Vide !\n");
		return;
	}

	while(l != NULL) {
		printf("%s ; ", toString(l->data));
		l = l->pNext; 
	}
}