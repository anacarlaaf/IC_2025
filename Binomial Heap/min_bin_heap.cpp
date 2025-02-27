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

//O(logn)
node *findMin(binomialHeap *t){
    //Passa por todas as roots de t comparando o valor minimo
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
    //Merge das árvores em ordem não-decrescente de degree
    node *i=b1->head, *j=b2->head, *aux, *st=NULL;

    // guardar o endereço do menor degree pra ser o novo b1->head;
    //cout << i << " " << j << "\n";
    if((i && !j) || ((i && j) && i->degree<=j->degree)){
        aux=i;
        st=i;
        i=i->sibling;
    }
    else if (j) {
        aux=j;
        st=j;
        j=j->sibling;
    }
    
    //merge
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

    //resto
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
    b2->head=NULL; // limpar a b2
}

//priv
// void linkTrees(node *t1, node *t2){
//     t2->parent =t1;
//     t1->child = t2;
//     t1->degree++;
// }

void uniteBinomialHeaps(binomialHeap *b1, binomialHeap *b2){
    mergeTrees(b1, b2);
    if(!b1->head || !b1->head->sibling) return;

    node *prev=NULL, *at=b1->head, *next=at->sibling;

    while(at && next){
        //Degrees diferentes ou degree do próximo do próximo igual ao atual
        if((at->degree!=next->degree) || (next->sibling && at->degree==next->sibling->degree)){
            //cout << "caso1 ou 2 \n";
            prev=at;
            at=at->sibling;
            next=next->sibling;
        }

        // Mesmo degrees, compara as chaves
        else if(at->key<=next->key){
            //cout << "caso3 \n";
            //linkTrees(at, next);
            at->sibling=next->sibling;
            next->sibling = at->child;
            at->child=next;
            next->parent=at;
            at->degree++;

            next=at->sibling;
        }
        else{
            //cout << "caso4 \n";
            //linkTrees(next, at);
            if(!prev) b1->head = next;
            else prev->sibling=next;
            at->sibling=next->child;
            next->child=at;
            at->parent=next;
            next->degree++;

            at=next;
            next=next->sibling;
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
}

void extractMin(binomialHeap *t){
    //encontrar o mínimo e remover da heap t
    node *ext = findMin(t), *aux;

    if(ext==t->head) {
        t->head=NULL;
        if(!ext->child && !ext->sibling) return;
    }
    else {
        aux = t->head;
        while(aux->sibling){
            if(aux->sibling==ext){
                aux->sibling=aux->sibling->sibling;
                break;
            }
            aux = aux->sibling;
        }
    }

    // tornar filhos do min em roots do novo heap
    binomialHeap t2;
    makeBinomialHeap(&t2);
    node *at, *next;
    aux = ext->child;
    if(aux && aux->sibling){
        at=aux->sibling;
        aux->parent=aux->sibling=NULL;
        while(at){
            at->parent=NULL;
            next = at->sibling;
            at->sibling=aux;
            aux=at;
            at=next;
        }
    }
    t2.head=aux;
    if(!t->head) t->head = ext->sibling;
    uniteBinomialHeaps(t, &t2);
    free(ext);
}

void decreaseKey(binomialHeap *t){

}

int main(){
    binomialHeap t1, t2;
    
    makeBinomialHeap(&t1);
    makeBinomialHeap(&t2);

    //int v[11] = {7,2,4,17,1,11,6,8,15,10,20}; //ok
    //int v2[7] = {10, 5, 3, 8, 12, 1, 7}; // ok

    //int v3[5] = {9, 3, 6, 12, 15}; // union ok
    //int v4[6] = {2, 8, 5, 10, 4, 7};

    int v5[8] = {5, 5, 5, 2, 2, 8, 8, 1}; // ok

    //int v6[1] = {42}; // ok

    //int v7[6] = {10, 8, 6, 4, 2, 0}; //ok

    //int v8[5] = {-3, -1, -5, -2, -4}; //ok

    for(int i : v5) insert(&t1, i);

    for(int i=0;i<8;i++){
        cout << "Min: " << findMin(&t1)->key << "\n";
        extractMin(&t1);
    }
    return 0;
}