#include "ex1.h"

//Core function for the first exercice
void program1(char *path, int nbElements){
    printf("Program 1 : Adding names to AVL tree and output png after each insertion ...\n");
    _list L = NULL; 
    _avlTree root=NULL;
    //Create a list containing the nbElements first names of the file FILE_P1
    L=readFile(path, nbElements);
    //Add the words within an AVL tree
    while (L!= NULL){
        insertAVL(&root,L->data);
        createDotAVL(root,"Tree");
        L = L->pNext;
    }
    printf("Done\n");
}

_list readFile (char *path, int nbElements)
{
	char word[100];
	_list L = NULL;
	FILE *file=NULL;

	file=fopen(path,"r+");
	if (nbElements==0){
		while (fgets(word, 100, file)!=NULL){
			word[strcspn(word, "\n")] = 0;
			word[strcspn(word, "\r")] = 0;
			L=addNode (strdup(word), L);
		}
	}else{
		for (int i = 0; i<nbElements; i++){
			fgets(word, 100, file);
			word[strcspn(word, "\n")] = 0;
			word[strcspn(word, "\r")] = 0;
			L=addNode (strdup(word), L);
		}
	}
	return L;
}
		
	
