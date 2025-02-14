#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

typedef struct pq{
    int tam;
    vector<int> q;

    pq() : tam(0) {}
} pq;

//O(logn)
void corrigeUp(pq *pQ){
    int i = pQ->tam-1, aux;
    while(i>=1 && pQ->q[(i-1)/2]>pQ->q[i]){
        aux = pQ->q[(i-1)/2];
        pQ->q[(i-1)/2] = pQ->q[i];
        pQ->q[i] = aux;
        i=(i-1)/2;
    }
}

//O(logn)
void corrigeDown(pq *pQ, int i){
    int j = i, tam = pQ->tam, f, aux;
    while (2*j+1<tam){
        f=2*j+1;

        if (f+1<tam && pQ->q[f] > pQ->q[f+1]){ 
            f=f+1;
        }

        if (pQ->q[j] <= pQ->q[f]){
            j = tam;
        }
        else{
            aux = pQ->q[j];
            pQ->q[j] = pQ->q[f];
            pQ->q[f] = aux;
            j=f;
        }
    }
}

//------

//O(nlogn)
void constroiHeap(vector<int> *v, pq *newPq){
    newPq->q = *v;
    newPq->tam = v->size();
    for (int i=newPq->tam; i>=0; i--){
        corrigeDown(newPq, i);
    }
} 

//O(logn)
void insere(pq *pQ, int item){
    pQ->q.push_back(item);
    pQ->tam++;
    corrigeUp(pQ);
}

//O(logn)
int remove_min(pq *pQ){
    if(pQ->tam==0){
        return NULL;
    }
    int men = pQ->q[0];
    pQ->q[0] = pQ->q[pQ->tam-1];
    pQ->tam--;
    corrigeDown(pQ, 0);
    pQ->q.pop_back();
    return men;
}

//O(1)
int men(pq *pQ){
    if(pQ->tam==0){
        return NULL;
    }
    return pQ->q[0];
}

int main(){
    int tam, x;

    printf("Ler e Inserir Itens:\n");
    scanf("%d", &tam);
    pq pQ;
    for(int i=0; i<tam; i++){
        scanf("%d", &x);
        insere(&pQ, x);
    }
    
    printf("\nPriority Queue:\n");
    for(int i=0; i<pQ.tam; i++){
        printf("%d ", pQ.q[i]);
    }

    printf("\n\nMostrar Min: %d", men(&pQ));
    printf("\nRemove Min: %d\n", remove_min(&pQ));

    printf("\nPriority Queue:\n");
    for(int i=0; i<pQ.tam; i++){
        printf("%d ", pQ.q[i]);
    }

    printf("\n\nInserir: ");
    scanf("%d", &x);
    insere(&pQ, x);

    printf("\nPriority Queue:\n");
    for(int i=0; i<pQ.tam; i++){
        printf("%d ", pQ.q[i]);
    }

    printf("\n\nHeapify Itens:\n");
    scanf("%d", &tam);
    vector<int> v;
    pq newPq;
    for(int i=0; i<tam; i++){
        scanf("%d", &x);
        v.push_back(x);
    }
    constroiHeap(&v, &newPq);
    printf("\nPriority Queue:\n");
    for(int i=0; i<newPq.tam; i++){
        printf("%d ", newPq.q[i]);
    }
}