#include <stdio.h>
#include <stdlib.h>

int ar[100000000];

// para cada elemento até metade do array, 
// verifica se os filhos (2*i e 2*i+1) são menores
char verifica(int a[], int tam){
    for(int i=1; i<=tam/2; i++){ 
        if (2*i<=tam && a[2*i]>a[i]){
            return 0;
        }
        if (2*i+1<=tam && a[2*i+1]>a[i]){
            return 0;
        }
    }
    return 1;
}

// se eu tenho um novo elemento no final e sei que 
// tudo antes é um heap binário,
// enquanto o elemento for maior que o pai, troco
void corrigeU(int a[], int tam){
    int i = tam, aux;
    while(i>=2 && a[i/2]<a[i]){
        aux = a[i/2];
        a[i/2] = a[i];
        a[i] = aux;
        i = i/2;
    }
}

// enquanto o filho não passar do fim do array, 
// verifica se um dos filhos é maior, se sim troca 
// com o pai e repete o processo para o filho trocado
// O(lgn)
void corrigeD(int a[], int tam, int i){
    int j = i, f, aux;
    while (2*j<=tam){ // enquanto o 1st filho estiver dentro do limite
        f=2*j;
        // se 2nd filho estiver dentro do limite, verifica qual dos filhos é maior
        if (f+1<=tam && a[f] < a[f+1]){ 
            f=f+1;
        }
        // se o pai for maior que o maior filho, termina
        if (a[j] >= a[f]){
            j = tam;
        }
        else{ // se não, troca o pai pelo maior filho
            aux = a[j];
            a[j] = a[f];
            a[f] = aux;
            j=f;
        }
    }
}

// Para cada elemento da metade do array até o 1st elemento, corrigir descendo
// O(n)
void constroi(int a[], int tam){
    for (int i=tam/2; i>=1; i--){
        corrigeD(a, tam, i);
    }
}

// insere um item no final do array, atualiza o tamanho e corrige subindo
void insere(int a[], int *tam, int item){
    a[*tam+1] = item;
    *tam += 1;
    corrigeU(a, *tam);
}

int remove_max(int a[], int *tam){
    int max = a[1]; // guarda o 1st elemento do array
    a[1] = a[*tam]; // coloca o último elemento no topo
    *tam -= 1; // atualiza o tamanho
    corrigeD(a, *tam, 1); // corrige descendo a partir do topo
    return max;
}

int max(int a[]){
    return a[1];
}

int main(){
    FILE *f;
    f = fopen("test_cases.txt", "r");
    int tam, ok=0, now, tot = 0;
    while (fscanf(f, "%d", &tam)==1){
        tot++;
        now = 0;
        ar[0] = tam;
        for (int j=1;j<=tam;j++){
            fscanf(f, "%d", &ar[j]);
        }

        constroi(ar, ar[0]);
        now += verifica(ar, ar[0]);

        remove_max(ar, &ar[0]);
        now += verifica(ar, ar[0]);

        insere(ar, &ar[0], 100);
        now += verifica(ar, ar[0]);

        if (now==3){
            ok++;
        } else{
            printf("\n%d %d\n", tot, tam);
        }
    }
    fclose(f);

    printf("Corretos: %d\n", ok);
    printf("Incorretos: %d\n", tot-ok);
    
    return 0;
}