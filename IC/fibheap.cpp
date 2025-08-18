#include<stdio.h>
#include<cstdlib>
#include <iostream>

using namespace std;

typedef struct node{
    int v;
    node *left;
    node *right;
    node *child;
    node *parent;
} node;

typedef struct fibHeap{
    node *mini;
    int nNodes;
} fibHeap;

void createFibHeap(fibHeap *f){
    f->mini = NULL;
    f->nNodes = 0;
}

void insert(fibHeap *f, int n){
    node *novo = (node*)malloc(sizeof(node));
    novo->v = n;

    if(!f->mini){
        f->mini = novo;
        return;
    }

    node *aux = f->mini->left;
    f->mini->left = novo;
    novo -> left = aux;
    if(n < f->mini->v) f->mini = novo;
}

int main(){

    return 0;
}