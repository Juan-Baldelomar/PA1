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

int testProperty4(RBTree *rbTree, Nodo *root){
    if (root == rbTree->NIL)
        return 1;
    if (root->color == 'R'){
        if (root->left->color != 'B' && root->right->color != 'B'){
            printf("ERROR: propery 4 violated \n");
            return 0;
        }
    }
    int r = testProperty4(rbTree, root->left);
    return r * testProperty4(rbTree, root->right);
}


int testTreeInsertion(){
    RBTree *rbTree = createTree();
    int status = 1;
    int n = 100;
    for (int i = 0; i<n; i++){
        put(rbTree, 100-i, 100-i);
    }
    traverse(rbTree);
    int height = getHeight(rbTree);
    int black_h = getBlackHeight(rbTree);
    printf("height: %d  black height: %d\n", height, black_h);
    printf("testing property 4\n");

    status &= (black_h>-1);
    status &= testProperty4(rbTree, rbTree->root);
    freeTree(&rbTree);
    return status;
}

int testTreeInsertion2(){
    RBTree *rbTree = createTree();
    int n = 100;
    int status = 1;
    for (int i = 0; i<n; i++){
        put(rbTree, i, i);
    }
    traverse(rbTree);
    int height = getHeight(rbTree);
    int black_h = getBlackHeight(rbTree);
    printf("height: %d  black height: %d\n", height, black_h);
    printf("testing property 4\n");

    status &= (black_h>-1);
    status &= testProperty4(rbTree, rbTree->root);
    freeTree(&rbTree);
    return status;
}

int testTreeInsertion3(){
    RBTree *rbTree = createTree();
    int n = 100;
    int status = 1;
    for (int i = 0; i<n; i++){
        int x = getRandom(1, 100);
        put(rbTree, x, x);
    }
    traverse(rbTree);
    int height = getHeight(rbTree);
    int black_h = getBlackHeight(rbTree);
    printf("height: %d  black height: %d\n", height, black_h);
    printf("testing property 4\n");
    status &= (black_h>-1);
    status &= testProperty4(rbTree, rbTree->root);
    freeTree(&rbTree);
    return status;
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
    freeTree(&tree);
    return flag;
}



int testTreeDeletion(){
    RBTree *rbTree = createTree();
    int n = 100;
    int status = 1;
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
    status &= (black_h>-1);
    status &= testProperty4(rbTree, rbTree->root);
    freeTree(&rbTree);
    return status;
}

int testTreeDeletion2(){
    RBTree *rbTree = createTree();
    int n = 100;
    int status = 1;
    int nodesToDelete[100];
    for (int i = 0; i<n; i++){
        int x = getRandom(1, 100);
        nodesToDelete[i] = x;
        put(rbTree, x, x);
    }

    for(int i = 0; i<n; i++){
        delete(rbTree, nodesToDelete[i]);
    }

    put(rbTree, 1, 1);

    traverse(rbTree);
    int height = getHeight(rbTree);
    int black_h = getBlackHeight(rbTree);
    printf("height: %d  black height: %d\n", height, black_h);
    printf("testing property 4\n");
    status &= (black_h>-1);
    status &= testProperty4(rbTree, rbTree->root);
    freeTree(&rbTree);
    return status;
}



int main() {
    printf("***************************************************************** INIT TESTS *****************************************************************\n");
    srand(time(0));
    int all_tests_ok;
    all_tests_ok = testTreeInsertion();
    all_tests_ok &= testTreeInsertion2();
    all_tests_ok &= testTreeInsertion3();
    all_tests_ok &= testTreeDeletion();
    all_tests_ok &= testTreeDeletion2();
    all_tests_ok &= testTools_simple();
    printf("******************************************************* ASSERT TESTS *************************************************************\n");
    assert(all_tests_ok);
    return 0;
}