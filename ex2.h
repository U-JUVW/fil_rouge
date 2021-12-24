#include <time.h>	//Used to compute execution time
#include <math.h>	//Used to compute the min height

#include "ex1.h"

//Prototypes
void program2(char * path);
void printStats(int length, int nbWords, double timeExec, int nbNodes, int hMin);
void getAnagrams(char * input, _avlTree root);
int getAnagramTree(char * path, _avlTree * pRoot);