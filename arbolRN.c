//
// Created by juan on 17/10/20.
//

#include "arbolRN.h"
#include "stdlib.h"
#include "stdio.h"

Nodo *createNode(int key, int val){
    Nodo *n = (Nodo*)malloc(sizeof(Nodo));
    if (n== NULL){
        printf("ERR NODE: Could not allocate memory\n");
        return NULL;
    }
    n->key = key;
    n->val = val;
    n->color = 'R';
    return n;
}

RBTree *createTree(){
    RBTree *rbTree = (RBTree*)malloc(sizeof(RBTree));
    if (rbTree == NULL){
        printf("ERR TREE: Could not allocate memory\n");
        return NULL;
    }
    rbTree->NIL = createNode(0, 0);
    rbTree->NIL->color = 'B';
    rbTree->root = rbTree->NIL;
    return rbTree;
}


void leftRotate(RBTree *rbTree, Nodo *x){
    Nodo  *y = x->right;
    x->right = y->left;             // y left subtree into x's subtree
    if (y->left != rbTree->NIL){    // verificar hijo izquierdo no es NIL y redefinir su padre
        y->left->parent = x;
    }
    y->parent = x->parent;          // redefinir padre de y

    if (x->parent == rbTree->NIL)   // verificar si x es la raiz
        rbTree->root = y;           // y es la nueva raiz
    else if (x==x->parent->left)
        x->parent->left = y;        // si x es hijo izquierdo
    else
        x->parent->right = y;       // si x es hijo derecho

    y->left = x;                    // hijo izq de y es x
    x->parent = y;                  //redefinir padre de x
}

void rightRotate(RBTree *rbTree, Nodo *x){
    Nodo  *y = x->left;
    // redefinir hijo izquierdo
    x->left = y->right;
    // verificar hijo derecho no es NIL y redefinir su padre
    if (y->right != rbTree->NIL){
        y->right->parent = x;
    }
    // redefinir padre de y
    y->parent = x->parent;

    // verificar si x es la raiz
    if (x->parent == rbTree->NIL)
        // y es la nueva raiz
        rbTree->root = y;
    else if (x==x->parent->left)
        // si x es hijo izquierdo
        x->parent->left = y;
    else
        // si x es hijo derecho
        x->parent->right = y;
    //redefinir padre de x
    y->right = x;
    x->parent = y;
}


void insertFixup(RBTree *rbTree, Nodo *z){
    Nodo *uncle;
    Nodo *parent;
    Nodo *grandp;
    parent = z->parent;
    grandp = parent->parent;
    while(parent->color == 'R'){
        // z.p is RED, it cannot be the root so z.p.p exists
        if (parent == grandp->left){
            uncle = grandp->right;
            if (uncle->color == 'R'){
                parent->color = 'B';
                uncle->color = 'B';
                grandp->color = 'R';

                z = grandp;                     // redefine z as grandp and verify properties
                parent = z->parent;
                grandp = parent->parent;
            } else{
                if (z == parent->right){        // transform to do a rigth rotate
                    z = parent;
                    leftRotate(rbTree, z);
                    parent = z->parent;         // redefine var parent and grandp
                    grandp = parent->parent;
                }
                parent->color = 'B';
                grandp->color = 'R';
                rightRotate(rbTree, grandp);
            }
        }else{
            uncle = grandp->left;
            if (uncle->color == 'R'){
                parent->color = 'B';
                uncle->color = 'B';
                grandp->color = 'R';

                z = grandp;                     // redefine z as grandp and properties for grandparent
                parent = z->parent;
                grandp = parent->parent;
            } else{
                if (z == parent->left){         // transform to do a left rotate
                    z = parent;
                    rightRotate(rbTree, z);
                    parent = z->parent;         // redefine var parent and grandp
                    grandp = parent->parent;
                }
                parent->color = 'B';
                grandp->color = 'R';
                leftRotate(rbTree, grandp);
            }
        }
    }// while z.p.color
    rbTree->root->color = 'B';
}


void put(RBTree *rbTree, int key, int val){
    Nodo *z = createNode(key, val);
    Nodo *y = rbTree->NIL;
    Nodo *x = rbTree->root;

    while(x!= rbTree->NIL){         //find leaf nodes
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == rbTree->NIL)           // tree is empty
        rbTree->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;
    z->left = rbTree->NIL;          //define children for new node
    z->right = rbTree->NIL;
    insertFixup(rbTree, z);
}


// metodos utiles para probar buen funcionamiento

int getNodeHeight(RBTree *rbTree, Nodo *root){
    if (root == rbTree->NIL)
        return 0;
    int left_h = getNodeHeight(rbTree, root->left);
    int right_h = getNodeHeight(rbTree, root->right);
    return left_h > right_h? left_h + 1 : right_h + 1;
}

int getBlackNodeHeight(RBTree *rbTree, Nodo *root){
    if (root == rbTree->NIL)
        return 1;
    int left_h = getBlackNodeHeight(rbTree, root->left);
    int right_h = getBlackNodeHeight(rbTree, root->right);

    if (left_h != right_h){
        printf("ERROR: RED-BLACK PROPERTY 5 violated\n");
    }

    return root->color == 'B' ? left_h + 1 : left_h;
}


void traverseNode(RBTree *rbTree, Nodo *root){
    if (root == rbTree->NIL)
        return;

    // in order traverse
    traverseNode(rbTree, root->left);
    printf("%d\n", root->key);
    traverseNode(rbTree, root->right);
}

void traverse(RBTree *rbTree){
    traverseNode(rbTree, rbTree->root);
}

int getHeight(RBTree *rbTree){
    return getNodeHeight(rbTree, rbTree->root);
}
int getBlackHeight(RBTree *rbTree){
    return getBlackNodeHeight(rbTree, rbTree->root);
}