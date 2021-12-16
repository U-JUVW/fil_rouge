#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


_list readFile (char *nom, int nbElements)
{
	char chaine[30];
	_list L = NULL;
	FILE *fichier=NULL;
	fichier=fopen(nom,"r+");

	if (nbElements==0){
		while (fgets(chaine, 30, fichier)!=NULL){
			L=addNode (strdup(chaine), L);
		}
	}else{
		for (int i = 0; i<nbElements; i++){
			fgets(chaine, 30, fichier);
			L=addNode (strdup(chaine), L);
			}
	}
	return L;
}
		
	
