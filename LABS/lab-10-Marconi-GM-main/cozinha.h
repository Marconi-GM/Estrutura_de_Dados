#ifndef COZINHA_H
#define COZINHA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "maxheap.h"

// nomes tem, no máximo, 15 caracteres + 1 caracter '\0'
#define NOME 16
// o nome do prato tem, no máximo, 25 caracteres
#define TAM_PRATO 26
// operação( pode ser ou altera (alterar prioridade) ou novo (novo prato))
#define OPERACAO 7

typedef struct fila_de_prioridade FP;

// struct que representa um sobrevivente
typedef struct survivor
{
    char nome[NOME];
    char sobrenome[NOME];

    int dias_sobrevividos;
    int id;

}survivor;

// struct que representa um pedido
typedef struct pedidos
{
    char prato[TAM_PRATO];

    int id;
    int prioridade;

}pedidos;

// registra os sobreviventes e armazenas seus dados para futuras consultas
void registra_sobreviventes(survivor *sobreviventes, int numero_sobreviventes);

// recebe e registra os novos pedidos e as alterações dos já existentes
void pedidos_e_alteracoes(FP *fila, survivor *sobreviventes, int N);

// entrega os pedidos
void entrega_de_pedidos(FP *fila, survivor *sobreviventes, int panelas);

// efetua os acontecimentos da rodada
int rodadas(FP *fila, survivor *sobreviventes, int panelas);


#endif

