#ifndef BINHEAP_H
#define BINHEAP_H

typedef struct pq{
    int tam;
    int q[1000000];
} pq;

void corrigeUp(pq *pQ){
    int i = pQ->tam-1, *a = pQ->q, aux;
    while(i>=1 && a[(i-1)/2]>a[i]){
        aux = a[(i-1)/2];
        a[(i-1)/2] = a[i];
        a[i] = aux;
        i=(i-1)/2;
    }
}

void corrigeDown(pq *pQ, int i){
    int j = i, tam = pQ->tam, f, *a=pQ->q, aux;
    while (2*j+1<tam){
        f=2*j+1;

        if (f+1<tam && a[f] > a[f+1]){ 
            f=f+1;
        }

        if (a[j] <= a[f]){
            j = tam;
        }
        else{
            aux = a[j];
            a[j] = a[f];
            a[f] = aux;
            j=f;
        }
    }
}

//------

void constroiHeap(pq *pQ){
    int tam=pQ->tam-1;
    for (int i=(tam-1)/2; i>=0; i--){
        corrigeDown(pQ, i);
    }
} 

void insere(pq *pQ, int item){
    pQ->q[pQ->tam] = item;
    pQ->tam++;
    corrigeUp(pQ);
}

int remove_min(pq *pQ){
    int max = pQ->q[0];
    pQ->q[0] = pQ->q[pQ->tam-1];
    pQ->tam--;
    corrigeDown(pQ, 0);
    return max;
}

int max(pq *pQ){
    return pQ->q[0];
}

#endif
