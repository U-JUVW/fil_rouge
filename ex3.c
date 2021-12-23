#include "ex3.h"

void program3(char * path){
	_avlTree root = NULL;
	_listAVLtree anagrams = NULL;
	int nbAnagrams = 0;
	getAnagramTree(path, &root);
	getAnagramNodes(&anagrams, &nbAnagrams, root);

	printf("\n");
	printf("Nombre d'anagrammes : %d\n",nbAnagrams);
	printf("**********************************************\n");
	printAnagrams(anagrams);

	//Tri de anagrams 
	// Relation d'ordre sur getLength(anagrams->data->words)
	//
}


void getAnagramNodes(_listAVLtree * pAnagrams,int * pNbAnagrams, _avlTree root){
	if(root == NULL){
		return;
	}

	//Ajouter à la liste 
	int len = getLength(root->words);
	if(len != 1){
		*pAnagrams = addNodeAVL(root,*pAnagrams);
		*pNbAnagrams += len; 
	}
	//getAnagramNodes arbre gauche
	getAnagramNodes(pAnagrams, pNbAnagrams, root->left);
	//getAnagramNodes arbre droite
	getAnagramNodes(pAnagrams, pNbAnagrams, root->right);
}

void printAnagrams(_listAVLtree anagrams){

	while(anagrams != NULL){
		// AFICHER
		// anagrams -> data -> words
		printf("Anagrammes pour la signature %s (%d):\n",anagrams->data->value,getLength(anagrams->data->words));
		showList(anagrams->data->words);
		printf("\n");

		anagrams = anagrams -> pNext;
	}

}
