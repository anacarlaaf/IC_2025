#include<stdio.h>
#include<cstdlib>
#include <iostream>

using namespace std;

typedef struct node{
    int key;
    int degree;
    node *parent;
    node *child;
    node *sibling;
} node;

typedef struct binomialHeap{
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

//priv
void mergeTrees(binomialHeap *b1, binomialHeap *b2){
    node *i=b1->head, *j=b2->head, *aux,*st=NULL;

    if(i && j && i->degree<=j->degree){
        aux=i;
        st=i;
        i=i->sibling;
    }
    else if (j) {
        aux=j;
        st=j;
        j=j->sibling;
    }

    while(i && j){
        if(i->degree<=j->degree){
            aux->sibling=i;
            aux=i;
            i=i->sibling;
        }
        else{
            aux->sibling=j;
            aux=j;
            j=j->sibling;
        }
    }

    while(i){
        aux->sibling=i;
        aux=i;
        i=i->sibling;
    }

    while(j){
        aux->sibling=j;
        aux=j;
        j=j->sibling;
    }

    b1->head=st;
    b2->head=NULL;
}

//priv
void linkTrees(node *t1, node *t2){
    t2->parent =t1;
    t1->child = t2;
    t1->degree++;
}

void uniteBinomialHeaps(binomialHeap *b1, binomialHeap *b2){

    mergeTrees(b1, b2);

    if(!b1->head) return;

    node *prev=NULL, *at=b1->head, *next=at->sibling;

    //cout << "start\n";
    while(at && next){
        if((at->degree!=next->degree) || (next->sibling && at->degree==next->sibling->degree)){
            //cout << "caso1 ou 2 \n";
            prev=at;
            at=at->sibling;
            next=next->sibling;
        }
        else if(at->key<=next->key){
            //cout << "caso3 \n";
            linkTrees(at, next);
            at->sibling=next->sibling;
            next->sibling = at->child;
        }
        else{
            //cout << "caso4 \n";
            linkTrees(next, at);
            if(!prev) b1->head = next;
            else prev->sibling=next;
            at->sibling = next->child;
        }
    }
}

void insert(binomialHeap *b1, int val){
    node *newNode = (node*) malloc(sizeof(node));
    newNode->key = val;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->degree = 0;
    newNode->sibling = NULL;
    
    binomialHeap b2;
    b2.head = newNode;

    uniteBinomialHeaps(b1,&b2);
    //cout << "end\n";
}

void remove(binomialHeap *t){

}

void decreaseKey(binomialHeap *t){

}


int main(){
    binomialHeap t;
    makeBinomialHeap(&t);
    insert(&t, 7);
    insert(&t, 8);
    insert(&t, 100);
    insert(&t, 1);
    insert(&t, 20000);
    insert(&t, 0);

    return 0;
}