#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


_list readFile (char *path, int nbElements)
{
	char word[100];
	_list L = NULL;
	FILE *file=NULL;

	file=fopen(path,"r+");
	if (nbElements==0){
		while (fgets(word, 100, file)!=NULL){
			L=addNode (strdup(word), L);
		}
	}else{
		for (int i = 0; i<nbElements; i++){
			fgets(word, 100, file);
			L=addNode (strdup(word), L);
		}
	}
	return L;
}
		
	
