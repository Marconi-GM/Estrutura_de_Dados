#ifndef SISTEMA_H
#define SISTEMA_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// número de caracteres que o nome de uma família possui, no máximo
#define FAMILIA 11

// número máximo de inserção de famílias no sistema
#define MAX_FAMILIAS 1499

// número de caracteres que o nome e sobrenome possui, no máximo
#define CRIANCA 11

// número escolhido para o tamanho da tabela de hashing 
#define MAX 1499

// struct sistema, possui 4 campos:
// o nome da familia cadastrada no sistema
// a quantidade de doces que ela possui
// a informação se a família saiu 
// e a informação se tal endereço da tabela de hashing está ocupado
typedef struct sistema
{
    char familia[FAMILIA];
    int qtde_doces;
    int familia_saiu;

    int endereco_vazio;

}sistema;

// dado um caracter qualquer, a função calcula seu ascii em binário e o retorna
int char_para_binario(char caracter);

// calcula o hash, dado um nome de familia
int hash(char *familia, int i);

// calcula outro hash nos casos em que já há um objeto na tabela de hash com o 
// mesmo número de hash
int hash_duplo(char *familia);

// adiciona a familia ao sistema
void inclui_familia(sistema *banco_de_dados, char familia[], int doces);

// encontra o hash da familia no sistema e o devolve
int encontra_familia(sistema *banco_de_dados, char familia[]);

// remove a familia do sistema
void remove_familia(sistema *banco_de_dados, char familia[]);

// atualiza a quantidade de doces de uma familia
void atualiza_qtde_doces(sistema *banco_de_dados, char familia[], int doces);

// trick or treat
void trickortreat(sistema *banco_de_dados, char nome[], char sobrenome[], int casas);

// cria um sistema
sistema *cria_sistema();

#endif
