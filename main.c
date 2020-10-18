#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "arbolRN.h"

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
int main() {
    srand(time(0));
    testTreeInsertion();
    testTreeInsertion2();
    testTreeInsertion3();
    printf("Should be 1: %d\n",testTools_simple());
    return 0;
}
