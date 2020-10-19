//
// Created by juan on 18/10/20.
//

#include "tests.h"
#include "arbolRN.h"
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

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

int testTools_simple(){
    RBTree *tree=NULL;
    int keys[]={1,2,3,4,5,6,7,8,9,10};
    int values[]={10,9,8,7,6,5,4,3,2,1};
    int flag=1;
    if(isEmpty(tree)!=-1) flag = 0;
    tree = createTree();
    if(isEmpty(tree)!=1) flag = 0;
    for(int i=0; i<10; i++){
        put(tree,keys[i],values[i]);
        if(contains(tree,keys[i])!=1){
            printf("Error in contains\n");
            flag = 0;}
        if(size(tree)!=keys[i]){
            printf("Error in size\n");
            flag = 0;}
        if(get(tree,keys[i])!=values[i]){
            printf("Error in get\n");
            flag = 0;}
    }
    if(contains(tree,11)!=0) flag=0;
    return flag;
}



void testTreeDeletion(){
    RBTree *rbTree = createTree();
    int n = 100;
    int nodesToDelete[100];
    for (int i = 0; i<n; i++){
        int x = getRandom(1, 100);
        nodesToDelete[i] = x;
        put(rbTree, x, x);
    }

    delete(rbTree, nodesToDelete[50]);
    delete(rbTree, nodesToDelete[20]);
    delete(rbTree, nodesToDelete[5]);
    delete(rbTree, nodesToDelete[0]);

    traverse(rbTree);
    int height = getHeight(rbTree);
    int black_h = getBlackHeight(rbTree);
    printf("height: %d  black height: %d\n", height, black_h);
    printf("testing property 4\n");
    testProperty4(rbTree, rbTree->root);
}

void testTreeDeletion2(){
    RBTree *rbTree = createTree();
    int n = 100;
    int nodesToDelete[100];
    for (int i = 0; i<n; i++){
        int x = getRandom(1, 100);
        nodesToDelete[i] = x;
        put(rbTree, x, x);
    }

    for(int i = 0; i<n; i++){
        delete(rbTree, nodesToDelete[i]);
    }

    traverse(rbTree);
    int height = getHeight(rbTree);
    int black_h = getBlackHeight(rbTree);
    printf("height: %d  black height: %d\n", height, black_h);
    printf("testing property 4\n");
    testProperty4(rbTree, rbTree->root);
}

void testTreeDeletion3(){
    RBTree *rbTree = createTree();
    int n = 100;
    int nodesToDelete[100];
    put(rbTree, 2, 2);
    put(rbTree, 1, 1);
    put(rbTree, 3, 3);

    Nodo *nodo = search(rbTree, 1);
    nodo->color = 'B';
    nodo = search(rbTree, 3);
    nodo->color = 'B';

    delete(rbTree, 1);

    traverse(rbTree);
    int height = getHeight(rbTree);
    int black_h = getBlackHeight(rbTree);
    printf("height: %d  black height: %d\n", height, black_h);
    printf("testing property 4\n");
    testProperty4(rbTree, rbTree->root);
}


int main() {
    srand(time(0));
    //testTreeInsertion();
    //testTreeInsertion2();
    //testTreeInsertion3();
    testTreeDeletion2();
    printf("Should be 1: %d\n",testTools_simple());
    return 0;
}