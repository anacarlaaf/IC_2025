#ifndef MIN_HEAP_BIN_H
#define MIN_HEAP_BIN_H

#include <vector>

using namespace std;

typedef struct pq {
    int tam;
    vector<int> q;

    pq() : tam(0) {}
} pq;


void insere(pq *pQ, int item);

/**
 * Remove e retorna o elemento mínimo da heap
 * Complexidade: O(log n)
 * @param pQ Ponteiro para a estrutura de heap
 * @return O elemento mínimo ou NULL se a heap estiver vazia
 */
int remove_min(pq *pQ);

/**
 * Retorna o elemento mínimo sem remover
 * Complexidade: O(1)
 * @param pQ Ponteiro para a estrutura de heap
 * @return O elemento mínimo ou NULL se a heap estiver vazia
 */
int men(pq *pQ);

#endif // MIN_HEAP_BIN_H