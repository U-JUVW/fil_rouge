#include "ex2.h"

//Let's define the "signature" of a word as the letters of this word sorted in alphabetic order


//Core function for the second exercise
void program2(char * path){
	_avlTree root = NULL;
    //Variables used for stats
    int length, nbWords, nbNodes, hMin;
    double execTime;
    //Variable to get the processor clock time before and after the creation of the AVL tree
    clock_t begin, end;
    //Variable used to check if the user wants to search for anagrams
    int boolean = 1;

    begin = clock();
	//AVL tree creation
    nbWords = getAnagramTree(path, &root);
    end = clock();

    execTime = (double) (end - begin) / CLOCKS_PER_SEC;         //Get the time spent on tree creation
    nbNodes = nbNodesAVL(root);                                 //Get the number of nodes
    length = strlen(root->value);                               //Get the length of the words (same one for each element)
    hMin = (int) log2(nbNodes);                                 //Compute the min height for a tree with the same number of nodes
    printStats(length, nbWords, execTime, nbNodes, hMin);       //Print those stats

    //Loop for anagram search
    while(1){
        char input[30];
        printf("+---------------------------+\n");
        printf("| Rechercher un anagramme ? |\n|   0 : NON   |   1 : OUI   |\n+---------------------------+\n ► ");
        //Check whether the user wants to search for anagrams
        scanf("%d",&boolean);   
        if(boolean == 0){       //If no, return
            break;
        }
        printf(" ► Saisir un mot : ");
        scanf("%s",input);                      //Get the reference word
        getAnagrams(input, root);                //Print the list of anagrams
    }
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


/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          void getAnagrams                                                                        ||
 ||                                                                                                             ||
 || DESCRIPTION :       Prints the anagrams of a word using an AVL tree containing signatures and the words     ||
 ||                     associated with this signature. If the input signature is not within the AVL tree,      ||
 ||                     send a negative response.                                                               ||
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     char *          input       ->           Word whose anagrams will be searched                           ||
 ||     _avlTree        root        ->           AVL tree containing signatures and their associated words      ||
 ||                                                                                                             ||
 || OUTPUT :            NONE                                                                                    ||
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
void getAnagrams(char * input, _avlTree root){
    int depth;
    clock_t begin, end;
    double execTime;
    char * key = sortstr(input);                            //Get the signature of the input   

    begin = clock();
    _avlTree pNode = searchAVL_it(root, key);               //Look for the node containing this signature
    end = clock();    

    //Case of a word that is not in the dictionnary
    if(pNode == NULL){
        printf("\nCe mot ne figure pas dans le dictionnaire\n");
        return;
    }

    execTime = (double) (end - begin) / CLOCKS_PER_SEC;     //Compute search time
    depth = heightAVL(root) - heightAVL(pNode);             //Compute depth of the node

    //Print the result
    printf("\t| Liste des anagrammes : ");
    showList(pNode->words);
    printf("\n");
    printf("\t| Profondeur du noeud : %d\n",depth);
    printf("\t| Temps de recherche : %fs\n",execTime);
}


//Print the stats
void printStats(int length, int nbWords, double execTime, int nbNodes, int hMin){ 
    printf("Statistiques de l'arbre : \n");
    printf("\t| Longueur des mots : %d\n",length);
    printf("\t| Nombre de mots : %d\n",nbWords);
    printf("\t| Temps de création : %fs\n",execTime);
    printf("\t| Nombre de noeuds : %d\n", nbNodes);
    printf("\t| Hauteur minimale : %d\n",hMin);
}