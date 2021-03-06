#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "ex3.h"

int main(int argc, char const *argv[])
{
    if(argc < 2){
        printf("Missing argument. Please enter the file path while executing the program.\nCorrect usage : <.exe path> <arg1>\n\t| arg1 : File path\n");
        return 1;
    }
    program3(strdup(argv[1]));
    return 0;
}

//Core function for the third exercise
void program3(char * path){
    _avlTree root = NULL;
    _listAVLtree anagrams = NULL;
    int nbAnagrams = 0;

    getAnagramTree(path, &root);                        //Get the AVL tree containing the anagrams
    getAnagramNodes(&anagrams, &nbAnagrams, root);      //Get the list of nodes containing anagrams (ie more than 1 word)
                                                        //  and the number of anagrams within the whole file

    printf("\n");
    printf("Number of anagrams : %d\n",nbAnagrams);
    printf("**********************************************\n");
    printAnagrams(anagrams);                                            //Print the lists of anagrams, sorted by descending length
}

/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          void getAnagramNodes                                                                    ||
 ||                                                                                                             ||
 || DESCRIPTION :       Recursively gets the list of AVL tree nodes containing anagrams and th number of        ||
 ||                     anagrams within the wole file.                                                          ||
 ||                     Edits the variables pointed by the parameters (exept for the AVL tree)                  || 
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     _listAVLtree *  pAnagrams   ->          Pointer to the list of AVL tree whose root contains anagrams    ||
 ||     int *           pNbAnagrams ->          Pointer to the number of anagrams within the whole file         ||
 ||     _avlTree        root        ->          AVL tree containing the signatures and their associated words   ||
 ||                                                                                                             ||
 || OUTPUT :            NONE                                                                                    ||  
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
void getAnagramNodes(_listAVLtree * pAnagrams,int * pNbAnagrams, _avlTree root){
    //Case of an empty tree
    if(root == NULL){
        return;
    }
    //Add current AVL tree to the list if there are anagrams within the root
    int len = getLength(root->words);
    if(len != 1){
        *pAnagrams = addNodeAVLList(root,*pAnagrams);
        *pNbAnagrams += len; 
    }
    
    getAnagramNodes(pAnagrams, pNbAnagrams, root->left);        //Get anagrams in the left subtree
    getAnagramNodes(pAnagrams, pNbAnagrams, root->right);       //Get anagrams in the right subtree
}


/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          _listAVLtree anagrams                                                                   ||
 ||                                                                                                             ||
 || DESCRIPTION :       Prints the anagrams from a linked list of AVL trees                                     ||
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     _listAVLtree    anagrams    ->          Linked list of AVL trees                                        ||
 ||                                                                                                             ||
 || OUTPUT :            NONE                                                                                    ||  
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
void printAnagrams(_listAVLtree anagrams){

    //Iterate through the linked list
    while(anagrams != NULL){
        //Print anagrams
        printf("Anagrams with the letters %s (%d):\n",anagrams->data->value,getLength(anagrams->data->words));   
        showList(anagrams->data->words);    
        printf("\n");

        anagrams = anagrams -> pNext;
    }

}
