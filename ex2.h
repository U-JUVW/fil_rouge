#include <time.h>
#include <math.h>

#include "ex1.h"

void program2(char * path);
void printStats(int length, int nbWords, double timeExec, int nbNodes, int hMin);
void getAnagram(char * input, _avlTree root);
int getAnagramTree(char * path, _avlTree * pRoot);