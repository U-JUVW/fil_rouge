#include "ex2.h"

void program2(char * path){
	_avlTree root = NULL;
    int length;
    int nbWords;
    int nbNodes;
    int hMin;
    double timeExec;
    clock_t begin = clock();
    clock_t end;
    int boolean = 1;

	//Lecture du fichier
	nbWords = getAnagramTree(path, &root);
    end = clock();
	//Calcul des caractéristiques de l'arbre
    timeExec = (double) (end - begin) / CLOCKS_PER_SEC;
    nbNodes = nbNodesAVL(root);
    length = strlen(root->value);
    hMin = (int) log2(nbNodes);
    printStats(length, nbWords, timeExec, nbNodes, hMin);

	//scanf pour la recherche dans l'abre
    printf("");
    while(1){
        char input[30];
        printf("+---------------------------+\n");
        printf("| Rechercher un anagramme ? |\n|   0 : NON   |   1 : OUI   |\n+---------------------------+\n ► ");
        scanf("%d",&boolean);
        if(boolean == 0){
            break;
        }
        printf(" ► Saisir un mot : ");
        scanf("%s",input);
        //condition de sortie -> boolean = 0;
        getAnagram(input, root);
    }
}

int getAnagramTree(char * path, _avlTree * pRoot){
    _list L = NULL;
    int nbWords = 0;
    L = readFile(path, 0);
    printf("Ajout des mots dans l'arbre ...\n");
    //Ajout des elements dans l'arbre
    while(L != NULL){
        nbWords ++;
        _avlTree temp = insertAVL(pRoot, sortstr(L->data));
        temp->words = addNode(L->data, temp->words);
        L = L->pNext;
    }
    return nbWords;
}

void printStats(int length, int nbWords, double timeExec, int nbNodes, int hMin){    
    printf("Longueur des mots : %d\n",length);
    printf("Nombre de mots : %d\n",nbWords);
    printf("Temps d'execution : %fs\n",timeExec);
    printf("Nombre de noeuds : %d\n", nbNodes);
    printf("Hauteur minimale : %d\n",hMin);
}

void getAnagram(char * input, _avlTree root){
    int depth;
    clock_t begin;
    clock_t end;
    double timeExec;

    char * key = sortstr(input);
    begin = clock();
    _avlTree pNode = searchAVL_it(root, key);
    end = clock();    
    timeExec = (double) (end - begin) / CLOCKS_PER_SEC;
    depth = heightAVL(root) - heightAVL(pNode);

    if(pNode == NULL){
        printf("\nCe mot ne figure pas dans le dictionnaire\n");
        return;
    }
    printf("\t| Liste des anagrammes : ");
    showList(pNode->words);
    printf("\n");
    printf("\t| Profondeur du noeud : %d\n",depth);
    printf("\t| Temps de recherche : %fs\n",timeExec);
}