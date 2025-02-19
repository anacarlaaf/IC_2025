#include<stdio.h>

using namespace std;

typedef struct{
    int key;
    int degree;
    node *parent;
    node *child;
    node *sibling;
} node;

typedef struct{
    node *head;
} binomialHeap;

void makeBinomialHeap(binomialHeap *t){
    t->head=NULL;
}

node *findMin(binomialHeap *t){
    node *aux = t->head, *minNode=aux;
    int minKey = aux->key;
    aux = aux->sibling;
    while(aux){
        if(aux->key<minKey){
            minKey = aux->key;
            minNode = aux;
        }
        aux = aux->sibling;
    }
    return minNode;
}

void uniteBinomialHeaps(binomialHeap *t1, binomialHeap *t2){
    
}

void insertNode(binomialHeap *t){

}

void removeNode(binomialHeap *t){

}

void decreaseKey(binomialHeap *t){

}


int main(){
    binomialHeap t;
    makeBinomialHeap(&t);
    return 0;
}