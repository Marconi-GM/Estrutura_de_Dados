#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arvore arvore;

// struct arvore, contendo a expressão (caractér) e os ponteiros para a sub
// arvore direita e esquerda
struct arvore
{
    char expressao;
    arvore *dir;
    arvore *esq;
};

// dado as subarvores, esquerda e direita, cria um novo nó da arvoré
arvore *cria_arvore(char expressao, arvore *esq, arvore *dir);

// otimiza as expressoes, quando possivel, reescrevendo a arvore
arvore *otimiza_arvore(arvore *arv);

// monta a arvore
arvore *monta_arvore(char expressao[]);

// imprime a arvore
void imprime_arvore(arvore *arv);

// libera a memória alocada para uso da árvore
void destroi_arvore(arvore *arv);