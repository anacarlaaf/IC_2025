#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

#include <climits> // Para INT_MIN

// Estrutura de um nó da heap binomial
typedef struct node {
    int key;                // Valor armazenado no nó
    int degree;             // Grau do nó (número de filhos)
    struct node *parent;    // Ponteiro para o pai
    struct node *child;     // Ponteiro para o primeiro filho
    struct node *sibling;   // Ponteiro para o próximo irmão
} node;

// Estrutura da heap binomial
typedef struct binomialHeap {
    node *head;             // Ponteiro para a primeira árvore binomial
} binomialHeap;

/**
 * Inicializa uma nova heap binomial vazia
 * @param t Ponteiro para a heap binomial a ser inicializada
 */
void makeBinomialHeap(binomialHeap *t);

/**
 * Encontra o nó com a chave mínima na heap
 * Complexidade: O(log n)
 * @param t Ponteiro para a heap binomial
 * @return Ponteiro para o nó com a chave mínima
 */
node *findMin(binomialHeap *t);

/**
 * Verifica se a heap está vazia
 * @param b1 Ponteiro para a heap binomial
 * @return true se a heap estiver vazia, false caso contrário
 */
bool isEmpty(binomialHeap *b1);

/**
 * Insere um novo valor na heap binomial
 * Complexidade: O(log n)
 * @param b1 Ponteiro para a heap binomial
 * @param val Valor a ser inserido
 */
void insert(binomialHeap *b1, int val);

/**
 * Remove e retorna o nó com a chave mínima da heap
 * Complexidade: O(log n)
 * @param t Ponteiro para a heap binomial
 */
void extractMin(binomialHeap *t);

/**
 * Decrementa o valor de uma chave na heap
 * Complexidade: O(log n)
 * @param t Ponteiro para a heap binomial
 * @param x Ponteiro para o nó cuja chave será decrementada
 * @param n Novo valor para a chave (deve ser menor que o valor atual)
 */
void decreaseKey(binomialHeap *t, node *x, int n);

/**
 * Remove um nó específico da heap
 * Complexidade: O(log n)
 * @param t Ponteiro para a heap binomial
 * @param x Ponteiro para o nó a ser removido
 */
void deleteKey(binomialHeap *t, node *x);

#endif // BINOMIAL_HEAP_H