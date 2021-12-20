#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "elt.h" // _element 
#include "list.h" // prototypes 

/*
typedef struct node {
	_element data;
	struct node *pNext;
} _listNode, * _list;
*/

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
		printf("%s ", toString(l->data));
		l = l->pNext; 
	}
}

void freeList(_list l) {
	// Libérer la mémoire de toutes les cellules de la liste l
	// A faire en itératif 

	_listNode * pAux; 
	// Il faut un pointeur auxiliaire : 
	// on ne doit libérer qu'après avoir enregistré quelque part
	// l'adresse de la maille suivante

	assert(l != NULL); 

	while(l != NULL) {
		printf("Libération de %s\n", l->data);
		pAux = l->pNext; 
		free(l); 
		l = pAux; 
	}
	printf("NULL");
}

_element getFirstElt(_list l) {
	// Renvoyer l'élément contenu dans la cellule de tête de la liste

	assert(l != NULL); 

	return l->data; 
}

_list removeFirstNode(_list l) {
	// Supprimer la tête de la liste 
	// Renvoyer la nouvelle liste privée de sa première cellule

	assert(l!= NULL);	
	_listNode * p =l->pNext; 
	free(l); 
	return p; 
}

// A produire en version récursive (+ tard dans le sujet)

void showList_rec(_list l) {
	// Afficher la liste en commençant par sa tête 
	// A faire en récursif 

	if (l == NULL) {
		// case de base
		return;
	} else {
		// cas général
		printf("%s ", toString(l->data));
		showList_rec(l->pNext); 
	}
}

void showList_inv_rec(_list l) {
	// Afficher la liste en commençant par sa queue 
	// A faire en récursif 

	if (l == NULL) {
		// case de base
		return;
	} else {
		// cas général
		showList_inv_rec(l->pNext); 
		printf("%s ", toString(l->data));	
	}
}

void freeList_rec(_list l) {
	// Libérer la mémoire de toutes les cellules de la liste l 
	// A faire en récursif

	if (l == NULL) {
		return;
	} else {
		freeList_rec(l->pNext);
		printf("Libération de %s\n",toString(l->data));
		free(l); 
	}
}

