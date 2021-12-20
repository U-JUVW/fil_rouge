#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>

#include "elt.h"
#include "avl.h"

//Prototypes of static functions
static _avlTree newNodeAVL(_element e);
static _avlTree rotateRightAVL(_avlTree A);
static _avlTree rotateLeftAVL(_avlTree A);
static _avlTree balanceAVL(_avlTree A);

//Output path for PNG & DOT files
char * outputPath = ".";


/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          static _avlTree newNodeAVL                                                              ||
 ||                                                                                                             ||
 || DESCRIPTION :       Creates a new AVL tree with a single node having its key initialized to a specific value||
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     _element        e           ->           Key that will be contained by the node                         ||
 ||                                                                                                             ||
 || OUTPUT :                                                                                                    ||
 ||     _avlTree        pNewTree    ->           Pointer to a node containing the value e                       ||
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
static _avlTree newNodeAVL(_element e){
    _avlTree pNewTree;
    pNewTree = (_avlTree) malloc(sizeof(_avlNode));     //Allocate required memory
    assert(pNewTree != NULL);                           //Terminate the program if the memory allocation failed

    pNewTree -> value = duplicateElt(e);                //Duplicate the element according to its type (cf elt.c)
    pNewTree -> words = NULL;
    pNewTree -> left = NULL;
    pNewTree -> right = NULL;
    pNewTree -> balance = 0;
    return pNewTree;
}

/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          static _avlTree rotateRightAVL                                                          ||
 ||                                                                                                             ||
 || DESCRIPTION :       Performs a right rotation of an AVL tree and corrects the balancing coefficients        ||
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     _avlTree        A           ->          Pointer to the root of the AVL tree to be rotated               ||
 ||                                                                                                             ||
 || OUTPUT :                                                                                                    ||
 ||     _avlTree        B           ->          Pointer to the root of the AVL tree after a right rotation      ||
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
static _avlTree rotateRightAVL(_avlTree A){
    _avlTree B = A -> left;
    //Keep in memory the balance coefficients before rotation (used to compute new balance coefficients)
    int initBalB = B -> balance;
    int initBalA = A -> balance;    

    //Rotate to the right
    A -> left = B -> right;
    B -> right = A;

    //Compute new balance coefficients
    B-> right -> balance = initBalA - 1 - MAX(0,initBalB);
    B -> balance = initBalB - 1 + MIN(0,B->right->balance); 

    return B;
}

/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          static _avlTree rotateLeftAVL                                                           ||
 ||                                                                                                             ||
 || DESCRIPTION :       Performs a left rotation of an AVL tree and corrects the balancing coefficients         ||
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     _avlTree        A           ->          Pointer to the root of the AVL tree to be rotated               ||
 ||                                                                                                             ||
 || OUTPUT :                                                                                                    ||
 ||     _avlTree        B           ->          Pointer to the root of the AVL tree after a left rotation       ||
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
static _avlTree rotateLeftAVL(_avlTree A){
    _avlTree B = A -> right;
    //Keep in memory the balancing coefficients before rotation 
    int initBalB = B -> balance;
    int initBalA = A -> balance;

    //Rotate to the left
    A -> right = B -> left;
    B -> left = A;

    //Compute new balancing coefficients
    B-> left -> balance = initBalA + 1 - MIN(0,initBalB);
    B-> balance = initBalB + 1 + MAX(0,B->left->balance);

    return B;
}

/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          static _avlTree balanceAVL                                                              ||
 ||                                                                                                             ||
 || DESCRIPTION :       Balances an AVL tree assuming the balancing coefficients are correct                    ||
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     _avlTree        A           ->          Pointer to the root of the AVL tree to be rotated               ||
 ||                                                                                                             ||
 || OUTPUT :                                                                                                    ||
 ||     _avlTree                    ->          Pointer to the root of the AVL tree after balancing             ||
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
static _avlTree balanceAVL(_avlTree A){
    //If the tree tilt to the left...
    if(A->balance > 1){
        //If the sub tree tilt to the right, perform Left-Right rotation
        if(A-> left->balance < 0){
            A->left = rotateLeftAVL(A->left);
            return rotateRightAVL(A);
        }     
        //else, perform a simple Right rotation                                 
        return rotateRightAVL(A);
    }
    //If the tree tilt to the right...
    if(A->balance < -1){
        //If the sub tree tilt to the left, perform Right-Left rotation
        if(A->right->balance > 0){
            A -> right = rotateRightAVL(A->right);
            return rotateLeftAVL(A);
        }          
        //else, perform simple Left rotation        
        return rotateLeftAVL(A);
    }
    return A;
}

/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          avlTree insertAVL                                                                       ||
 ||                                                                                                             ||
 || DESCRIPTION :       Inserts a node in an AVL tree, balances the AVL tree and check if height icreased.      ||
 ||                     Modifies the AVL tree pointed by the first parameter. Returns a pointer to the new node ||
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     _avlTree *      pA          ->          Pointer to the pointer to the root of the AVL tree              ||
 ||                                             to be rotated                                                   ||
 ||     _element        e           ->          Element to be inserted in the AVL tree                          ||
 ||                                                                                                             ||
 || OUTPUT :                                                                                                    ||
 ||     _avlTree                    ->          Pointer to the added node                                       ||
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
_avlTree insertAVL(_avlTree *pA, _element e){
    const int height = heightAVL(*pA);
    //Create a stack that will contain the path followed to add the node
    _avlTree *path[height];
    int top = -1;

    //Create an int array to store the potential changes of balancing coefficients
    int *sides =  malloc(sizeof(int) * (height));

    int comparison;

    //Case of an empty tree
    if(*pA == NULL){
        *pA = newNodeAVL(e);
        free(sides);
        return *pA;
    }

    //While leaf are not reached
    while(*pA != NULL){ 
        //Add current pointer to the current subtree to the stack   
        top++;
        path[top] = pA;     
        comparison = compareElt(e,(*pA)->value);
        //If the element is less than the value in the current node
        if(comparison < 0){
            //Go to the left, add 1 to potential balance coefficient and continue the loop
            pA = &((*pA) -> left);
            sides[top] = 1;
            continue;
        }
        //If the element is greater than the value in the current node
        else if(comparison > 0){
            //Go to the right, add -1 to potential balance coefficient and continue the loop
            pA = &(*pA) -> right;
            sides[top] = -1;
            continue;
        }
        //Else, the element is equal to the value in the current node. Thus return 0 (duplicate values are not allowed).
        
        free(sides);
        return *pA;
    }

    //Add the element in the reached leaf
    *pA = newNodeAVL(e);

    //Reverse the path and balance the subtrees
    while(top >= 0){
        (*path[top])->balance += sides[top];        //Correct balancing coefficients according to the path followed
        *path[top] = balanceAVL(*path[top]);        //Balance current subtree
        if((*path[top])->balance == 0){             //If the subtree balancing coefficient is zero, there is no change for the parent nodes
            break;
        }
        top --;
    }
    _avlTree temp = *pA;
    //Reset pointer to the original tree
    pA = path[0];
    free(sides);
    return temp; 
}

/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          _avlTree searchAVL_rec                                                                  ||
 ||                                                                                                             ||
 || DESCRIPTION :       Recursively searches for an element in an AVL tree. If the element is found, returns a  ||
 ||                     pointer to the node containing the element.                                             ||
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     _avlTree        root        ->          Pointer to the root of the AVL tree in which the element        ||
 ||                                             will be searched                                                ||
 ||     _element        e           ->          Element to be searched                                          ||
 ||                                                                                                             ||
 || OUTPUT :                                                                                                    ||
 ||     _avlTree                    ->          Pointer to the node which contains the searched element.        ||
 ||                                             NULL if the element is not in the AVL tree.                     ||
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
_avlTree searchAVL_rec(_avlTree root, _element e){
    int comparison;

    //Case of an empty tree
    if(root == NULL){
        return NULL;
    }

    comparison = compareElt(e,root->value);
    //If e is smaller than the current node element
    if(comparison < 0){
        return(searchAVL_rec (root->left, e));          //Search within the left subtree
    }
    //Else, if e is greater than the current node element
    else if(comparison > 0){                           
        return searchAVL_rec(root->right,e);            //Search within the right subtree
    }
    //Otherwise, e is equal to the current node
    return root;    
}

/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          _avlTree searchAVL_rec                                                                  ||
 ||                                                                                                             ||
 || DESCRIPTION :       Iteratively searches for an element in an AVL tree. If the element is found, returns a  ||
 ||                     pointer to the node containing the element.                                             ||
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     _avlTree        root        ->          Pointer to the root of the AVL tree in which the element        ||
 ||                                             will be searched                                                ||
 ||     _element        e           ->          Element to be searched                                          ||
 ||                                                                                                             ||
 || OUTPUT :                                                                                                    ||
 ||     _avlTree                    ->          Pointer to the node which contains the searched element.        ||
 ||                                             NULL if the element is not in the AVL tree.                     ||
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
_avlTree searchAVL_it(_avlTree root, _element e){
    int comparison;

    while(root != NULL){
        comparison = compareElt(e,root->value);
        //If e is smaller than the current node element, check the left child
        if(comparison < 0){
            root = root->left;
        }
        //Else if e is greater than the current node element, check the right child
        else if (comparison > 0){
            root = root->right;
        }
        //Otherwise, e is equal to the current node
        return root;        
    }
    return NULL;
}

/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          int nbNodesAVL                                                                          ||
 ||                                                                                                             ||
 || DESCRIPTION :       Recursively computes the number of nodes of a given tree                                ||
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     _avlTree        A           ->          AVL tree whose number of node is to be calculated               ||
 ||                                                                                                             ||
 || OUTPUT :                                                                                                    ||
 ||     int                         ->          Number of node of the AVL tree                                  ||  
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
int nbNodesAVL(_avlTree A){
    //Case of an empty tree
    if(A == NULL){
        return 0;
    }
    //Return 1 plus the number of nodes in child trees
    return 1 + nbNodesAVL(A->right) + nbNodesAVL(A->left);
}


/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          int heightAVL                                                                           ||
 ||                                                                                                             ||
 || DESCRIPTION :       Recursively computes the height of a given AVL tree                                     ||
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     _avlTree        root        ->          AVL tree whose height is to be calculated                       ||
 ||                                                                                                             ||
 || OUTPUT :                                                                                                    ||
 ||     int                         ->          Height of the AVL tree                                          ||  
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
int heightAVL(_avlTree root){
    int leftHeight, rightHeight;

    //Case of an empty tree
    if(root == NULL){
        return -1;
    }
    //Recursively ompute the heights of the left and the right subtree
    leftHeight = heightAVL(root->left);
    rightHeight = heightAVL(root->right);

    //Return the max height found
    return 1 + MAX(leftHeight, rightHeight);
}

/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          void printAVL                                                                           ||
 ||                                                                                                             ||
 || DESCRIPTION :       Recursively prints the AVL tree in the terminal (horizontal orientation)                ||
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     _avlTree        root        ->          AVL tree whose height is to be calculated                       ||                                                                      ||
 ||     int             indent      ->          Number of identation for the current node                       ||
 ||                                                                                                             ||
 || OUTPUT :            NONE                                                                                    ||  
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
void printAVL(_avlTree root, int indent){
    //Case of an empty tree
    if(root == NULL){
        return;
    }
    //Print the righ subtree
    printAVL(root->right, indent + 1);
    //Indent before printing the element
    for(int i = 0; i < indent; i++){
        printf("\t");
    }
    //Print the value inside of root
    printf("%s\n", toString(root->value));
    //Print the left subtree
    printAVL(root->left, indent + 1);
}

/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          static void genDotAVL                                                                   ||
 ||                                                                                                             ||
 || DESCRIPTION :       Writes the content of an AVL tree in a dot file                                         ||
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     _avlTree        root        ->          AVL tree whose content is to be written in dot                  ||
 ||     FILE *          fp          ->          Pointer to the dot file                                         ||
 ||                                                                                                             ||
 || OUTPUT :            NONE                                                                                    ||  
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
static void  genDotAVL(_avlTree root, FILE *fp) {

    fprintf(fp, "\t\"%s\"",toString(root->value));
    fprintf(fp, " [label = \"{{<c> %s | %d}| { <g> | <d>}}\"];\n",toString(root->value),root->balance);
    if (root->right == NULL && root->left == NULL) {
        fprintf(fp, "\t\"%s\"", toString(root->value)); 
        fprintf(fp, " [label = \"{{<c> %s | %d}| { <g> NULL | <d> NULL}}\"];\n", toString(root->value),root->balance);
    }
    else if (root->right == NULL) {
        fprintf(fp, "\t\"%s\"", toString(root->value));
        fprintf(fp, " [label = \"{{<c> %s | %d}| { <g> | <d> NULL}}\"];\n", toString(root->value),root->balance);
    }
    else if ( root->left == NULL) {
        fprintf(fp, "\t\"%s\"",toString(root->value));
        fprintf(fp, " [label = \"{{<c> %s | %d}|{ <g> NULL | <d> }}\"];\n", toString(root->value),root->balance);
    
    }
    
    if (root->left) {
        fprintf(fp, "\t\"%s\"",toString(root->value));
        fprintf(fp, ":g -> \"%s\";\n", toString(root->left->value));
        genDotAVL(root->left, fp);
    }

    if (root->right) {
        fprintf(fp, "\t\"%s\"",toString(root->value));
        fprintf(fp,":d -> \"%s\";\n", toString(root->right->value));
        genDotAVL(root->right, fp);
    }
}

/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||                                                                                                             ||
 || FUNCTION :          static void genDotAVL                                                                   ||
 ||                                                                                                             ||
 || DESCRIPTION :       Generates the whole dot file to represent an AVL tree and print the result in a PNG file||
 ||                                                                                                             ||
 || PARAMETERS :                                                                                                ||
 ||     _avlTree        root        ->          AVL tree whose content is to be written in dot                  ||
 ||     char *          basename    ->          Base name of the files. A number wil be added if several files  ||
 ||                                             with the same name are generated during the execution.          ||
 ||                                                                                                             ||
 || OUTPUT :            NONE                                                                                    ||  
 ||                                                                                                             ||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
void createDotAVL(const _avlTree root, const char *basename) {
    static char oldBasename[FILENAME_MAX + 1] = "";
    static unsigned int noVersion = 0;

    char DOSSIER_DOT[FILENAME_MAX + 1]; 
    char DOSSIER_PNG[FILENAME_MAX + 1]; 

    char fnameDot [FILENAME_MAX + 1];
    char fnamePng [FILENAME_MAX + 1];
    char    cmdLine [2 * FILENAME_MAX + 20];
    FILE *fp;
    struct stat sb;
    

    // Au premier appel, création (si nécessaire) des répertoires
    // où seront rangés les fichiers .dot et .png générés par cette fonction    

    // il faut créer le répertoire outputPath s'il n'existe pas 
    if (stat(outputPath, &sb) == 0 && S_ISDIR(sb.st_mode)) {
    } else {
        printf("Création du répertoire %s\n", outputPath);
        mkdir(outputPath, 0777);
    }

    // il faut créer les répertoires outputPath/png et /dot 
    sprintf(DOSSIER_DOT, "%s/dot/",outputPath);
    sprintf(DOSSIER_PNG, "%s/png/",outputPath);

    if (oldBasename[0] == '\0') {
        mkdir(DOSSIER_DOT,  S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
        mkdir(DOSSIER_PNG,  S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    }

     // S'il y a changement de nom de base alors recommencer à zéro
     // la numérotation des fichiers 

    if (strcmp(oldBasename, basename) != 0) {
        noVersion = 0;
        strcpy(oldBasename, basename); 
    }

    sprintf(fnameDot, "%s%s_v%02u.dot", DOSSIER_DOT, basename, noVersion);
    sprintf(fnamePng, "%s%s_v%02u.png", DOSSIER_PNG, basename, noVersion);

    //CHECK_IF(fp = fopen(fnameDot, "w"), NULL, "erreur fopen dans saveDotBST"); 
    fp = fopen(fnameDot, "w");
    assert(fp!=NULL);
    
    noVersion ++;
    fprintf(fp, "digraph %s {\n", basename);
    fprintf(fp, 
        "\tnode [\n"
            "\t\tfontname  = \"Arial bold\" \n"
            "\t\tfontsize  = \"14\"\n"
            "\t\tfontcolor = \"red\"\n"
            "\t\tstyle     = \"rounded, filled\"\n"
            "\t\tshape     = \"record\"\n"
            "\t\tfillcolor = \"grey90\"\n"
            "\t\tcolor     = \"blue\"\n"
            "\t\twidth     = \"2\"\n"
            "\t]\n"
        "\n"
        "\tedge [\n"
            "\t\tcolor     = \"blue\"\n"
        "\t]\n\n"
    );

    if (root == NULL)
        fprintf(fp, "\n");
    else
        genDotAVL(root, fp);

    fprintf(fp, "}\n"); 
    fclose(fp);

    sprintf(cmdLine, "dot -Tpng  %s -o %s", fnameDot, fnamePng);
    system(cmdLine);

    //printf("Creation de '%s' et '%s' ... effectuee\n", fnameDot, fnamePng);
}
