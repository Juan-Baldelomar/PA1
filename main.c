#include <stdio.h>
#include "time.h"
#include "stdlib.h"
#include "arbolRN.h"

int getRandom(int base, int limit) {
    return base + rand() % (limit - base + 1);
}


void testProperty4(RBTree *rbTree, Nodo *root){
    if (root == rbTree->NIL)
        return;
    if (root->color == 'R'){
        if (root->left->color != 'B' && root->right->color != 'B'){
            printf("ERROR: propery 4 violated \n");
        }
    }
    testProperty4(rbTree, root->left);
    testProperty4(rbTree, root->right);
}


void testTreeInsertion(){
    RBTree *rbTree = createTree();
    int n = 100;
    for (int i = 0; i<n; i++){
        put(rbTree, 100-i, 100-i);
    }
    traverse(rbTree);
    int height = getHeight(rbTree);
    int black_h = getBlackHeight(rbTree);
    printf("height: %d  black height: %d\n", height, black_h);
    printf("testing property 4\n");
    testProperty4(rbTree, rbTree->root);
}

void testTreeInsertion2(){
    RBTree *rbTree = createTree();
    int n = 100;
    for (int i = 0; i<n; i++){
        put(rbTree, i, i);
    }
    traverse(rbTree);
    int height = getHeight(rbTree);
    int black_h = getBlackHeight(rbTree);
    printf("height: %d  black height: %d\n", height, black_h);
    printf("testing property 4\n");
    testProperty4(rbTree, rbTree->root);
}

void testTreeInsertion3(){
    RBTree *rbTree = createTree();
    Nodo *nodo;
    int n = 100;
    for (int i = 0; i<n; i++){
        int x = getRandom(1, 100);
        put(rbTree, x, x);
    }
    traverse(rbTree);
    int height = getHeight(rbTree);
    int black_h = getBlackHeight(rbTree);
    printf("height: %d  black height: %d\n", height, black_h);
    printf("testing property 4\n");
    testProperty4(rbTree, rbTree->root);
}


int main() {
    srand(time(0));
    testTreeInsertion();
    testTreeInsertion2();
    testTreeInsertion3();
    return 0;
}
