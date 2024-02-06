#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "cozinha.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define PAI(i) ((i - 1) / 2)
#define F_ESQ(i) (2 * i + 1)
#define F_DIR(i) (2 * i + 2)

typedef struct pedidos pedidos;

typedef struct survivor survivor;

// struct que será a fila de prioridades
typedef struct fila_de_prioridade
{
    pedidos *pedido;
    int n;

}FP;

// cria a fila
FP *cria_fila(int tamanho);

// troca a posição de dois pedidos, da fila de prioridade
void troca(pedidos *a, pedidos *b);

// efetua o registro de um novo pedido
void registra_pedido(FP *fila, survivor *sobrevivente);

// sobe um pedido na fila de prioridades
void sobe_no_heap(FP *fila, int id);

// devolve o pedido de maior prioridade
pedidos busca_pedido(FP *fila);

// desce um pedido na fila de prioridades
void desce_no_heap(FP *fila, int id);

// altera a prioridade de um pedido
void altera_prioridade(FP *fila, int id, int valor);

#endif