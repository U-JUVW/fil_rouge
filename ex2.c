#include <stdio.h>
#include <stdlib.h>

#include "avl.h"
#include "list.h"
#include "ex1.h"

void program2(char * path, int nbElements){
	_list L = NULL;
	_avlTree root = NULL;

	//Lecture du fichier
	
	L = readFile(path, nbElements);

	//Ajout des elements dans l'arbre
	while(L != NULL){
		char * str = sortstr(L->data);
		_avlTree temp = insertAVL(&root, sortstr(L->data));
		temp->words = addNode(L->data, temp->words);
		L = L->pNext;

	}
	//Calcul des caractéristiques de l'arbre

	//scanf pour la recherche dans l'abre
}