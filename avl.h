#include "elt.h"
#include "list.h"

#define MAX(a,b) ((a>b) ? a : b)
#define MIN(a,b) ((a>b) ? b : a)

typedef struct tNode{
    _element value;
    _list words;
    int balance;
    struct tNode* left;
    struct tNode* right;
}_avlNode, *_avlTree;

_avlTree insertAVL(_avlTree * pA, _element e);
int heightAVL(_avlTree root);
void printAVL(_avlTree root, int indent);
int nbNodesAVL(_avlTree A);
_avlTree searchAVL_rec(_avlTree root, _element e);
_avlTree searchAVL_it(_avlTree root, _element e);
void createDotAVL(const _avlTree root, const char *basename);