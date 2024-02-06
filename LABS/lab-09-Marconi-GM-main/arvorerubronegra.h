#ifndef ARVORERUBRONEGRA_H
#define ARVORERUBRONEGRA_H

#include "dracarys.h"

enum cor {VERMELHO, PRETO};

typedef struct arvore_rubro_negra arvore;

// árvore, contendo uma variavel, uma cor, e os endereços para as subarvores
// esquerda e direita
struct arvore_rubro_negra
{
   variavel *var;

   enum cor cor;

   arvore *esq;
   arvore *dir;

};

// verifica se o nó da arvore rubro negra é vermelho
int eh_vermelho(arvore *arv);

// verifica se o nó da árvore rubro negra é preto
int eh_preto(arvore *arv);

// insere um novo nó na árvore, ou a cria se ela for vazia
arvore *inserir_na_arvore(arvore *arv, variavel *var);

// mantém a condições para que a árvore seja uma árvore binária de busca
arvore *corrige_arvore(arvore *arv);

// rotaciona a árvore para a esquerda, quando a árvore não satisfaz as condições
// para ser uma árvore binária de busca
arvore *rotaciona_p_esquerda(arvore *arv);

// rotaciona a árvore para a direita, quando a árvore não satisfaz as condições
// para ser uma árvore binária de busca
arvore *rotaciona_p_direita(arvore *arv);

// libera toda a memória alocada para uso da árvore
void destroi_arvore(arvore *arv);

// altera a cor dos nós da árvore nos casos em que a árvore não satisfaz as con
// dições para ser uma árvore binária de busca
void sobe_vermelho(arvore *arv);

// realiza a impressão da árvore, em ordem alfabética
void imprime_simbolos(arvore *arv);

#endif
