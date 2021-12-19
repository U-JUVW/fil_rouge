#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "elt.h"
#include "avl.h"
#include "list.h"
#include "ex1.h"


#define FILE_P1 "PrenomsV2.txt"

//Prototypes
void program1(char *path,int nbElements);

int main(int argc, char const *argv[])
{
    int prog;
    if(argc < 4){
        printf("Missing arguments\n\targ1 : Program to be executed (1 to 3)\n\targ2 : Path to the file to be read\n\targ3 : Number of words to be read\nEnd of program\n");
        return 1;
    }

    prog = atoi(argv[1]);
    switch(prog){
        case 1 :
            program1(strdup(argv[2]), atoi(argv[3]));
            break;
        case 2:
            printf("Pas de programme 2 pour l'instant ! \n");
            break;
        case 3:
            printf("Pas de programme 3 pour l'instant ! \n");
            break;
        default:
            program1(strdup(argv[2]), atoi(argv[3]));
    }

    return 0;
}

//Program used for the first exercice
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
}