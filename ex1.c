#include "ex1.h"

//Core function for the first exercise
void program1(char *path, int nbElements){
    printf("Program 1 : Adding names to AVL tree and output png after each insertion ...\n");
    _list L = NULL; 
    _avlTree root=NULL;
    //Create a list containing the nbElements first names of the file FILE_P1
    L=readFile(path, nbElements);
    //Add the words within an AVL tree
    while (L!= NULL){
        insertAVL(&root,L->data);
        //Create PNG output after each insertion
        createDotAVL(root,"Tree");
        L = L->pNext;
    }    
    printf("Done\n");
}

/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          _list readFile                                                                          ||
 ||                                                                                                             ||
 || DESCRIPTION :       Reads words in a txt file where each line contains a word                               ||
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     char *          path        ->           Path to the file that will be read                             ||
 ||     int             nbElements  ->           Number of elements to be read. If 0, the whole document will   ||
 ||                                              be read.                                                       ||
 ||                                                                                                             ||
 || OUTPUT :                                                                                                    ||
 ||     _list *                     ->           Linked list of strings containing the words read               ||
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
_list readFile (char *path, int nbElements)
{
	char word[100];
	_list L = NULL;
	FILE *file=NULL;

	//Open the file
	file=fopen(path,"r+");

	//Case of reading the whole document
	if (nbElements==0){
		while (fgets(word, 100, file)!=NULL){
			//Remove \r and \n
			word[strcspn(word, "\n")] = 0;
			word[strcspn(word, "\r")] = 0;
			//Add the word to the list
			L=addNode (strdup(word), L);
		}
	}else{
		for (int i = 0; i<nbElements; i++){
			//Read the next line
			fgets(word, 100, file);
			//Remove \r and \n
			word[strcspn(word, "\n")] = 0;
			word[strcspn(word, "\r")] = 0;
			//Add the word to the list
			L=addNode (strdup(word), L);
		}
	}
	return L;
}
		
	
