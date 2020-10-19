#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "arbolRN.h"

int getRandom(int base, int limit) {
    return base + rand() % (limit - base + 1);
}

int main(){
    RBTree *rbTree = createTree();
    Nodo *nodo;
    int n = 100;
    int nodesToDelete[100];

    for (int i = 0; i<n; i++){
        int x = getRandom(0, 1000);
        nodesToDelete[i] = x;
        put(rbTree, x, x);
    }

    // put some keys that we know for sure that exist
    put(rbTree, 2500, 2500);
    put(rbTree, 3000, 3000);

    printf(" ********************************************** TREE IN ORDER **********************************************\n");
    traverse(rbTree);

    delete(rbTree, 2500);
    nodo = search(rbTree, 2500);
    if (nodo = rbTree->NIL){
        printf("Nodo 2500 no existe. (Funcionando Correctamente)\n");
    }

    nodo = search(rbTree, 3000);
    if (nodo != rbTree->NIL){
        printf("Nodo 3000 existe con valor: %d\n", nodo->val);
    }

    delete(rbTree, 3000);
    nodo = search(rbTree, 3000);
    if (nodo = rbTree->NIL){
        printf("Nodo 3000 no existe. (Funcionando Correctamente)\n");
    }


    printf("Tree size: %d", size(rbTree));

    printf(" *************************************** We are going to delete every node ***************************************\n");
    for (int i = 0; i<n; i++){
        delete(rbTree, nodesToDelete[i]);
    }

    printf("Is Tree Empty:%d\n", isEmpty(rbTree));
    traverse(rbTree);

    freeTree(&rbTree);
    return 0;
}
