#include <stdio.h>
#include <string.h>

#include "utils.h"

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

/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          int getAnagramTree                                                                      ||
 ||                                                                                                             ||
 || DESCRIPTION :       Modifies an AVL tree in which each node will contains a list of anagrams and a their    ||
 ||                     signature, and computes the number of anagrams in the whole dictionnary.                ||
 ||                     The dictionnary is a txt file whose path is given in parameters.                        ||
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     char *          path        ->           Path to the txt file that will be read                         ||
 ||     int             pRoot       ->           Pointer to the AVL tree that will be edited                    ||
 ||                                                                                                             ||
 || OUTPUT :                                                                                                    ||
 ||     int                         ->           Number of anagrams in the txt file                             ||
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
int getAnagramTree(char * path, _avlTree * pRoot){
    _list L = NULL;
    int nbWords = 0;
    L = readFile(path, 0);                          //Get the words from the file
    printf("Ajout des mots dans l'arbre ...\n");
    //Iterate through the list of words
    while(L != NULL){
        nbWords ++;
        //Try to insert a new node, get the pointer to the node containing the signature of the word
        _avlTree temp = insertAVL(pRoot, sortstr(L->data));
        //Add the word to the anagram list of this node
        temp->words = addNode(L->data, temp->words);
        L = L->pNext;
    }
    printf("Done\n");
    return nbWords;
}

