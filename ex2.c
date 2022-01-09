#include <stdio.h>
#include <string.h>
#include <time.h>   //Used to compute execution time
#include <math.h>   //Used to compute the min height

#include "utils.h"
#include "ex2.h"

//Let's define the "signature" of a word as the letters of this word sorted in alphabetic order


int main(int argc, char const *argv[])
{
    if(argc < 2){
        printf("Missing argument. Please enter the file path while executing the program.\nCorrect usage : <.exe path> <arg1>\n\t| arg1 : File path\n");
        return 1;
    }
    program2(strdup(argv[1]));
    
    return 0;
}

//Core function for the second exercise
void program2(char * path){
	_avlTree root = NULL;
    //Variables used for stats
    int length, nbWords, nbNodes, hMin, hAVL;
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
    hAVL = heightAVL(root);
    hMin = (int) log2(nbNodes);                                 //Compute the min height for a tree with the same number of nodes
    printStats(length, nbWords, execTime, nbNodes, hMin, hAVL);       //Print those stats

    //Loop for anagram search
    while(1){
        char input[30];
        printf("+---------------------------+\n");
        printf("|     Search anagrams ?     |\n|   0 : NO    |   1 : YES   |\n+---------------------------+\n ► ");
        //Check whether the user wants to search for anagrams
        scanf("%d",&boolean);   
        if(boolean == 0){       //If no, return
            break;
        }
        printf(" ► Enter a word or letters : ");
        scanf("%s",input);                       //Get the reference word
        getAnagrams(input, root);                //Print the list of anagrams
    }
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
        printf("\nThis word isn't in the given dictionary\n");
        return;
    }

    execTime = (double) (end - begin) / CLOCKS_PER_SEC;     //Compute search time
    depth = heightAVL(root) - heightAVL(pNode);             //Compute depth of the node

    //Print the result
    printf("\t| Angram list : ");
    showList(pNode->words);
    printf("\n");
    printf("\t| Depth of the node : %d\n",depth);
    printf("\t| Search time : %fs\n",execTime);
}


//Print the stats
void printStats(int length, int nbWords, double execTime, int nbNodes, int hMin, int hAVL){ 
    printf("Stats : \n");
    printf("  | Length of the words : %d\n",length);
    printf("  | Number of words : %d\n",nbWords);
    printf("  | Time to create the tree : %fs\n",execTime);
    printf("  | Number of nodes : %d\n", nbNodes);	
    printf("  | AVL tree height : %d\n",hAVL);
    printf("  | Minimal height : %d\n",hMin);
}
