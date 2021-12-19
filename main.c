#include <stdio.h>
#include <assert.h>

#include "elt.h"
#include "avl.h"
#include "list.h"
#include "ex1.h"


#define FILE_P1 "PrenomsV2.txt"

//Prototypes
void program1(int nbElements);

int main(int argc, char const *argv[])
{

    int n;
    if(argc > 1){
        printf("A\n");
        n = atoi(argv[1]);
        printf("B\n");
        program1(n);
    }
    return 0;
}

//Program used for the first exercice
void program1(int nbElements){
    _list L = NULL; 
    _avlTree root=NULL;
    //Create a list containing the nbElements first names of the file FILE_P1
    L=readFile(FILE_P1, nbElements);
    //Add the words within an AVL tree
    while (L!= NULL){
        insertAVL(&root,L->data);
        L = L->pNext;
    }
}