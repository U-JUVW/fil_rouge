#include <stdio.h>
#include <assert.h>

#include "elt.h"
#include "avl.h"

void testAVLImplem();

int main(int argc, char const *argv[])
{
    _avlTree A = NULL;
    insertAVL(&A, "Après-midi");
    createDotAVL(A, "ArbreA");
    //testAVLImplem();
    return 0;
}

/*
void testAVLImplem(){
    _avlTree root = NULL;
    insertAVL(&root,10);
    printf("\n\n****************************\n\n");
    printAVL(root,0);
    insertAVL(&root, 9);
    printf("\n\n****************************\n\n");
    printAVL(root,0);
    insertAVL(&root, 11);
    printf("\n\n****************************\n\n");
    printAVL(root,0);
    insertAVL(&root, 12);
    insertAVL(&root, 11);
    printf("\n\n****************************\n\n");
    printAVL(root,0);
    insertAVL(&root, 13);
    insertAVL(&root, 11);
    printf("\n\n****************************\n\n");
    printAVL(root,0);
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
    root = searchAVL_it(root,10);
    printAVL(root,0);
    createDotAVL(root, "test");
}
*/