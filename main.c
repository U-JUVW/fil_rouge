#include <stdio.h>
#include <assert.h>

#include "elt.h"
#include "avl.h"
#include "list.h"
#include "ex1.h"

void testAVLImplem();

int main(int argc, char const *argv[])
{

    _avlTree A = NULL;
    _list L = NULL; 
    _avlTree root=NULL;
    char nom[15];
    int n;  
    printf("Nom du fichier : ");
    scanf("%14s",nom);
    printf("Nombre d'éléments lus : ");
    scanf("%d",&n);
    L=readFile(nom, n);
    while (L!= NULL){
        insertAVL(&root,L->data);
        L = L->pNext;
    }
    createDotAVL(root, "Arbre_de_noms");

    //testAVLImplem();
    return 0;
}

/*
void testAVLImplem(){
    _avlTree root = NULL;
    insertAVL(&root,10);
    printf("\n\n****************************\n\n");
    printAVL(root,0);
    createDotAVL(root, "test");
    insertAVL(&root, 9);
    printf("\n\n****************************\n\n");
    printAVL(root,0);
    createDotAVL(root, "test");
    insertAVL(&root, 11);
    printf("\n\n****************************\n\n");
    printAVL(root,0);
    createDotAVL(root, "test");
    insertAVL(&root, 12);
    insertAVL(&root, 11);
    printf("\n\n****************************\n\n");
    printAVL(root,0);
    createDotAVL(root, "test");
    insertAVL(&root, 13);
    insertAVL(&root, 11);
    printf("\n\n****************************\n\n");
    printAVL(root,0);
    createDotAVL(root, "test");
    insertAVL(&root, 7);
    insertAVL(&root, 11);
    printf("\n\n****************************\n\n");
    printAVL(root,0);
    insertAVL(&root, 8);
    insertAVL(&root, 11);
    printf("\n\n****************************\n\n");
    printAVL(root,0);
    insertAVL(&root, 5);
    printf("\n\n****************************\n\n");
    printAVL(root,0);
    insertAVL(&root, 6);
    printf("\n\n****************************\n\n");
    printAVL(root,0);
    printf("Nombre de noeuds : %d\n", nbNodesAVL(root));
    createDotAVL(root, "test");
}
*/