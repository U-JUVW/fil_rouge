#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "elt.h"
#include "avl.h"

/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||																												||
 ||	FUNCTION :			static _avlTree newNodeAVL																||
 ||																												||
 ||	DESCRIPTION :		Creates a new AVL tree with a single node having its key initialized to a specific value||
 ||																												||
 ||	PARAMETERS :																								||
 ||		_element		e			->			Key that will be contained by the node	 			 			||
 ||																												||
 ||	OUTPUT :																									||
 ||		_avlTree	 	pNewTree	->			 Pointer to a node containing the value e						||
 ||																												||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
static _avlTree newNodeAVL(_element e){
	_avlTree pNewTree;
	pNewTree = (_avlTree) malloc(sizeof(_avlNode));		//Allocate required memory
	assert(pNewTree != NULL);							//Terminate the program if the memory allocation failed

	pNewTree -> value = duplicateElt(e);				//Duplicate the element according to its type (cf elt.c)
	pNewTree -> left = NULL;
	pNewTree -> right = NULL;
	pNewTree -> balance = 0;
	return pNewTree;
}

/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||																												||
 || FUNCTION :			static _avlTree rotateRightAVL															||
 ||																												||
 ||	DESCRIPTION :		Performs a right rotation of an AVL tree and corrects the balancing coefficients		||
 ||																												||
 ||	PARAMETERS :																								||
 ||		_avlTree		A			->			Pointer to the root of the AVL tree to be rotated	 			||
 ||																												||
 ||	OUTPUT :																									||
 ||		_avlTree	 	B			->			Pointer to the root of the AVL tree after a right rotation		||
 ||																												||
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
 ||																												||
 || FUNCTION :			static _avlTree rotateLeftAVL															||
 ||																												||
 ||	DESCRIPTION :		Performs a left rotation of an AVL tree and corrects the balancing coefficients			||
 ||																												||
 ||	PARAMETERS :																								||
 ||		_avlTree		A			->			Pointer to the root of the AVL tree to be rotated	 			||
 ||																												||
 ||	OUTPUT :																									||
 ||		_avlTree	 	B			->			Pointer to the root of the AVL tree after a left rotation		||
 ||																												||
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
	A -> balance = initBalA + 1 - MIN(0,initBalB);
	B-> balance = initBalB + 1 + MAX(0,B->left->balance);

	return B;
}

/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||																												||
 || FUNCTION :			static _avlTree balanceAVL																||
 ||																												||
 ||	DESCRIPTION :		Balances an AVL tree assuming the balancing coefficients are correct					||
 ||																												||
 ||	PARAMETERS :																								||
 ||		_avlTree		A			->			Pointer to the root of the AVL tree to be rotated	 			||
 ||																												||
 ||	OUTPUT :																									||
 ||		_avlTree	 	A			->			Pointer to the root of the AVL tree after balancing				||
 ||																												||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
static _avlTree balanceAVL(_avlTree A){
	//If the tree tilt to the right...
	if(A->balance > 1){
		//If the sub tree tilt to the left, perform Left-Right rotation
		if(A-> left->balance < 0){
			A->left = rotateLeftAVL(A->left);
			return rotateRightAVL(A);
		}		
		//else, perform a simple Right rotation									
		return rotateRightAVL(A);
	}
	//If the tree tilt to the left...
	if(A->balance < -1){
		//If the sub tree tilt to the right, perform Right-Left rotation
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
 ||																												||
 || FUNCTION :			void insertAVL																			||
 ||																												||
 ||	DESCRIPTION :		Inserts a node in an AVL tree, balances the AVL tree and check if height icreased.		||
 ||						Modifies the AVL tree pointed by the first parameter									||
 ||																												||
 ||	PARAMETERS :																								||
 ||		_avlTree *		pA			->			Pointer to the pointer to the root of the AVL tree 				||
 ||												to be rotated	 												||
 ||		_element		e			->			Element to be inserted in the AVL tree	 						||
 ||																												||
 ||	OUTPUT :			NONE																					||
 ||																												||
 |+-------------------------------------------------------------------------------------------------------------+|
 +===============================================================================================================+
 */
void insertAVL(_avlTree *pA, _element e){
	const int height = heightAVL(*pA);
	//Create a stack that will contain the path followed to add the node
	_avlTree *path[height];
	int top = -1;

	//Create an int array to store the potential changes of balancing coefficients
	int *sides =  malloc(sizeof(int) * (height));

	//Case of an empty tree
	if(*pA == NULL){
		*pA = newNodeAVL(e);
		return;
	}

	//While leaf are not reached
	while(*pA != NULL){	
		//Add current pointer to the current subtree to the stack 	
		top++;
		path[top] = pA;		

		//If the element is less than the value in the current node
		if(e < (*pA)->value){
			//Go to the left, add 1 to potential balance coefficient and continue the loop
			pA = &((*pA) -> left);
			sides[top] = 1;
			continue;
		}
		//If the element is greater than the value in the current node
		else if(e > (*pA) -> value){
			//Go to the right, add -1 to potential balance coefficient and continue the loop
			pA = &(*pA) -> right;
			sides[top] = -1;
			continue;
		}
		//Else, the element is equal to the value in the current node. Thus return 0 (duplicate values are not allowed).
		return;
	}

	//Add the element in the reached leaf
	*pA = newNodeAVL(e);

	//Reverse the path and balance the subtrees
	while(top >= 0){
		(*path[top])->balance += sides[top];			//Correct balancing coefficients according to the path followed
		*path[top] = balanceAVL(*path[top]); 			//Balance current subtree
		top --;
	}
	//Reset pointer to the original tree
	pA = path[0];
}


/**
 +===============================================================================================================+
 |+-------------------------------------------------------------------------------------------------------------+|
 ||																												||
 || FUNCTION :			int heightAVL																			||
 ||																												||
 ||	DESCRIPTION :		Recursively computes the height of a given AVL tree										||
 ||																												||
 ||	PARAMETERS :																								||
 ||		_avlTree 		root		->			AVL tree whose height is to be calculated						||
 ||																												||
 ||	OUTPUT :																									||
 ||		int							-> 			Height of the AVL tree											||	
 ||																												||
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
 ||																												||
 || FUNCTION :			void printAVL																			||
 ||																												||
 ||	DESCRIPTION :		Recursively prints the AVL tree in the terminal (horizontal orientation)				||
 ||																												||
 ||	PARAMETERS :																								||
 ||		_avlTree 		root		->			AVL tree whose height is to be calculated						||																		||
 ||		int		 		indent		->			Number of identation for the current node						||
 ||																												||
 ||	OUTPUT :			NONE																					||	
 ||																												||
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
	printf("%d\n", root->value);
	//Print the left subtree
	printAVL(root->left, indent + 1);
}