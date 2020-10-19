//
// Created by juan on 17/10/20.
//

#ifndef PA1_T9_ARBOLRN_H
#define PA1_T9_ARBOLRN_H


typedef struct NodoStruct{
    struct NodoStruct* left;
    struct NodoStruct* right;
    struct NodoStruct* parent;
    char color;
    int val;
    int key;
}Nodo;

typedef struct ArbolRNStruct{
    Nodo *root;
    Nodo *NIL;
    int treeSize;
}RBTree;

Nodo *createNode(int key, int val);
RBTree *createTree();

// tabla de simbolos
void put(RBTree *rbTree, int key, int val);
int get(RBTree *rbTree, int key);
int contains(RBTree *rbTree, int key);
Nodo* search(RBTree *rbTree, int key);
void delete(RBTree *rbTree, int key);
int isEmpty(RBTree *rbTree);
int size(RBTree *rbTree);

// funciones utiles
void traverse(RBTree *rbTree);
int getHeight(RBTree *rbTree);
int getBlackHeight(RBTree *rbTree);
int countNodes(RBTree *t,Nodo *n);
#endif //PA1_T9_ARBOLRN_H
