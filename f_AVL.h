typedef struct nodeItem{
  int info;
  int balanceamento; // H(Esq) - H(dir)
  struct nodeItem *father;
  struct nodeItem *left;
  struct nodeItem *right;
} node;


int info(node *no);

int fb(node *no);

node *right(node *no);

node *left(node *no);

node *father(node *no);

node *brother(node *no);

int isLeft(node *no);

int isRight(node *no);

node *makeNode(int value);

void insertNode(node *no, int value);

node *addLeft(node *no, int value);

node *setNodeLeft(node *no, node *n);

node *addRight(node *no, int value);

node *setNodeRight(node *no, node *n);

int isLeaf(node *no);

node *nodeRoot(node *no);

void preOrdem(node *no);

void freeTree(node *no);

int level(node *n);

int maiorInfo(node *no);

void passNode(node *no, int *qtd);

int qtdNode(node *no);

int max(int a, int b);

int depth(node *no);

int depthTree(node *no);

node *searchByValue(node *no, int value);

void delNode(node *tree, int value);

void rotationRight(node *no);

void rotationLeft(node *no);

void rotationRightLeft(node *no);

void rotationLeftRight(node *no);

void setBalancing(node *no);

void checkBalancing(node *no);
