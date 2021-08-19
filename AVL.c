#include <stdio.h>
#include <stdlib.h>
#include "f_AVL.h"

int main(int argc, char const *argv[]) {
  //   RED
  // int vet[] = {4, 10, 3, 7, 5};
  // node *tree = makeNode(8);

  //  RD
  // int vet[] = {4, 10, 2, 6, 3};
  // node *tree = makeNode(8);

  //   RE
  // int vet[] = {10, 30, 25, 35, 40};
  // node *tree = makeNode(20);

  //   RDE
  int vet[] = {10, 30, 25, 35, 23};
  node *tree = makeNode(20);
  printf("\n INSERIR 20");
  for(int i=0; i<(sizeof(vet)/sizeof(int)); i++){
    insertNode(tree, vet[i]);
  }

  printf("\n Qtd No: %d \n", qtdNode(nodeRoot(tree)));

  printf("\n Pre Ordem: ");
  preOrdem(nodeRoot(tree));
  printf("\n");

  delNode(nodeRoot(tree), 23);

  delNode(nodeRoot(tree), 35);
  printf(" Pre Ordem: ");
  preOrdem(nodeRoot(tree));
  printf("\n\n");
  insertNode(nodeRoot(tree), 15);
  printf("\n Pre Ordem: ");
  preOrdem(nodeRoot(tree));
  printf("\n\n");

  insertNode(nodeRoot(tree), 5);

  printf("\n Pre Ordem: ");
  preOrdem(nodeRoot(tree));
  printf("\n\n");

  insertNode(nodeRoot(tree), 50);
  printf("\n Pre Ordem: ");
  preOrdem(nodeRoot(tree));
  printf("\n");
  delNode(nodeRoot(tree), 5);

  printf(" Pre Ordem: ");
  preOrdem(nodeRoot(tree));
  printf("\n");

  freeTree(nodeRoot(tree));
  printf("\n Arvore deletada!\n");

  return 0;
}

int info(node *no){
  return no->info;
}

int fb(node *no){
  return no->balanceamento;
}

node *right(node *no){
  return no->right;
}

node *left(node *no){
  return no->left;
}

node *father(node *no){
  return no->father;
}

node *brother(node *no){
  if(father(no) == NULL) return NULL;
  if(isRight(no)){
    return left(father(no));
  }else{
    return right(father(no));
  }
}

int isLeft(node *no){
if(father(no) == NULL) return 0;
  return left(father(no)) == no;
}

int isRight(node *no){
  if(father(no) == NULL) return 0;
  return right(father(no)) == no;
}

node *makeNode(int value){
  node *no = (node *)malloc(sizeof(node));
  no->info = value;
  no->father = NULL;
  no->left = NULL;
  no->right = NULL;
  no->balanceamento = 0;
  return no;
}


void insertNode(node *no, int value){
  if(isLeaf(no)){
    if(value > info(no)){
      printf(" INSERIR %d" ,value);
      setBalancing(addRight(no, value));
    }else{
      printf(" INSERIR %d" ,value);
      setBalancing(addLeft(no, value));
    }
  }else{
    if(value > info(no)){
      if(right(no) != NULL){
        insertNode(right(no), value);
      }else{
        printf(" INSERIR %d" ,value);
        setBalancing(addRight(no, value));
      }
    }else if(value <  info(no)){
      if(left(no) != NULL){
        insertNode(left(no), value);
      }else{
        printf(" INSERIR %d" ,value);
        setBalancing(addLeft(no, value));
      }
    }else{    /// IGUAL valor
      node *n = makeNode(value);
      n->right = no->right;
      n->father = no;
      no->right->father = n;
      no->right = n;
      setBalancing(n);
    }
  }
}

node *addLeft(node *no, int value){
  return setNodeLeft(no, makeNode(value));
}

node *setNodeLeft(node *no, node *n){
  no->left = n;
  n->father = no;
  return n;
}

node *addRight(node *no, int value){
  return setNodeRight(no, makeNode(value));
}

node *setNodeRight(node *no, node *n){
  no->right = n;
  n->father = no;
  return n;
}

int isLeaf(node *no){
  return no->left == NULL && no->right == NULL;
}

node *nodeRoot(node *no){
  if(father(no) != NULL){
    return nodeRoot(father(no));
  }else{
    return no;
  }
}

void preOrdem(node *no){
  if(no != NULL){
    printf(" [%d]", info(no));
    preOrdem(left(no));
    preOrdem(right(no));
  }
}

void freeTree(node *no){
  if (!isLeaf(no)){
    if(left(no) != NULL){
      freeTree(left(no));
    }
    if(right(no) != NULL){
      freeTree(right(no));
    }
    free(no);
  }
}


int level(node *n){
  if(father(n) != NULL){
    return level(father(n)) + 1;
  }
  return 0;
}

void passNode(node *no, int *qtd){
  *qtd = *qtd + 1;
  if(!isLeaf(no)){
    if(left(no) != NULL){
      passNode(left(no), qtd);
    }
    if(right(no) != NULL){
      passNode(right(no), qtd);
    }
  }
}

int qtdNode(node *no){
  int qtd = 0;
  passNode(no, &qtd);
  return qtd;
}

int max(int a, int b){
  return a > b ? a : b;
}

int depth(node *no){
  if(no == NULL || isLeaf(no)){
    return 0;
  }
  return max(depth(left(no)), depth(right(no))) + 1;
}

int depthTree(node *no){
  return depth(nodeRoot(no));
}

int maiorInfo(node *no){
  if(right(no) == NULL){
    return info(no);
  }else{
    return maiorInfo(right(no));
  }
}

node *searchByValue(node *no, int value){
  if(info(no) == value){
    return no;
  }
  if(value > info(no)){
    if(right(no) != NULL){
      return searchByValue(right(no), value);
    }else{
      return NULL;
    }
  }
  if(value < info(no)){
    if(left(no) != NULL){
      return searchByValue(left(no), value);
    }else{
      return NULL;
    }
  }
}

void rotationRight(node *no){
  printf("\n Rotacao Direita");
  node *aux = left(no);
  if(father(no) != NULL){
    if(left(father(no)) == no){
      no->father->left = aux;
    }else{
      no->father->right = aux;
    }
  }
  aux->father = father(no);
  no->father = aux;
  if(right(aux) != NULL){
    aux->right->father = no;
  }
  no->left = right(aux);
  aux->right = no;
  no->balanceamento = 0;
}

void rotationLeft(node *no){
  printf("\n Rotacao Esquerda");
  node *aux = right(no);
  if(father(no) != NULL){
    if(left(father(no)) == no){
      no->father->left = aux;
    }else{
      no->father->right = aux;
    }
  }
  aux->father = father(no);
  no->father = aux;
  if(left(aux) != NULL){
    aux->left->father = no;
  }
  no->right = left(aux);
  aux->left = no;
  no->balanceamento = 0;
}

void rotationRightLeft(node *no){
  rotationRight(right(no));
  rotationLeft(no);
  setBalancing(no);
}

void rotationLeftRight(node *no){
  rotationLeft(left(no));
  rotationRight(no);
  setBalancing(no);
}

void setBalancing(node *no){
  int alturaE=0, alturaD=0;
  if(right(no) != NULL){
    alturaD = depth(right(no))+1;
  }
  if(left(no) != NULL){
    alturaE = depth(left(no))+1;
  }
  no->balanceamento = alturaE - alturaD;
  checkBalancing(no);
  if(father(no) != NULL){
    setBalancing(father(no));
  }
}

void checkBalancing(node *no){
  if(no->balanceamento == 2){
    if(no->left->balanceamento == 1){
      rotationRight(no);
      setBalancing(no);
    }else{
      rotationLeftRight(no);
    }
  }else if(no->balanceamento == -2){
    if(no->right->balanceamento == -1){
      rotationLeft(no);
      setBalancing(no);
    }else{
      rotationRightLeft(no);
    }
  }
}

void delNode(node *tree, int value){
  node *no = searchByValue(tree, value);
  node *aux;
  if(no != NULL){
    if(isLeaf(no)){
      if(left(father(no)) == no){
        no->father->left = NULL;
      }else{
        no->father->right = NULL;
      }
      aux = father(no);
      free(no);
      if(aux != NULL){
        setBalancing(aux);
      }
      printf("\n Valor deletado! \n");
    }else if(no == tree){ // É a raiz
      if(left(tree) != NULL){
        tree->info = maiorInfo(left(tree));
        no = searchByValue(left(no), info(tree));
        delNode(no, info(no));
        setBalancing(tree);
      }else{
        no = right(tree);
        tree->right = right(no);
        tree->left = left(no);
        tree->info = info(no);
        no->right = NULL;
        no->left = NULL;
        delNode(no, info(no));
      }
    }else{
      aux = father(no);
      no->father = NULL;
      delNode(no, info(no));
      no->father = aux;
      setBalancing(no);
    }
  }else{
    printf("\n Valor %d nao encontrado para deletar!", value);
    return;
  }
}
