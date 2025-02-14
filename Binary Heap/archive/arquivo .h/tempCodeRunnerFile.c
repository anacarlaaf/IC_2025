#include <stdio.h>
#include <stdlib.h>
#include "binheap.h"

int main(){
    int tam, x;
    scanf("%d", &tam);
    
    pq pQ; pQ.tam = 0;
    for(int i=0; i<tam; i++){
        scanf("%d", &x);
        insere(&pQ, x);
    }

    // for(int i=0; i<tam; i++){
    //     printf("%d", pQ.q[i]);
    // }

}