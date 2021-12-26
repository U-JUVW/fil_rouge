#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "ex1.h"


int main(int argc, char const *argv[])
{
	if(argc < 2){
		printf("Missing argument. Please enter the file path while executing the program.\nCorrect usage : <.exe path> <arg1> <arg2>\n\t| arg1 : File path\n\t| arg2 : Number of word to be read (0 or empty to read the whole file)\n");
		return 1;
	}
	if(argc == 2){
		program1(strdup(argv[1]), 0);
	}else{
		program1(strdup(argv[1]), atoi(argv[2]));
	}
	return 0;
}

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

	
	
