#define MAX(a,b) ((a > b) ? a : b)
#define MIN(a,b) ((a > b) ? b : a)

typedef enum {	
	DOUBLE_RIGHT = -2,
	RIGHT = -1,
	BALANCED = 0,
	LEFT = 1,
	DOUBLE_LEFT = 2
}treeBalance;

typedef struct tNode{
	_element value;
	int balance;
	struct tNode* left;
	struct tNode* right;
}_avlNode, *_avlTree;

void insertAVL(_avlTree * pA, _element e);
int heightAVL(_avlTree root);
void printAVL(_avlTree root, int indent);

