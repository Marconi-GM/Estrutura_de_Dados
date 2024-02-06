#ifndef JOHNCC_H
#define JOHNCC_H

#include "dracarys.h"
#include "arvorerubronegra.h"

// verifica se há parenteses na linha lida do arquivo
int tem_parenteses(char *linha);

// verifica se a linha lida do arquivo começa com letra
int comeca_com_letra(char *linha);

// verifica se a linha lida do arquivo começa com int, double ou char
int eh_declaracao(char *linha);

// cria uma nova variavel para ser inserida na árvore
variavel *cria_variavel(char *linha);

// verifica se uma expressão  lida é valida
void verifica_expressao(char *linha, arvore *arv,int numero_da_linha, int *ha_erros);

// busca uma variável na árvore a fim de ver se ela foi declarada
int busca_na_arvore(arvore *arv, variavel *var, int linha);

// verifica se o resultado da expressão OP1 = OP2 operador OP3 é válida
int verifica_resultado(variavel *op1, variavel *op2, int linha);

// verifica os tipos das variáveis op2 e op3 a fim de ver se são compatíveis
int verifica_os_tipos(variavel *op2, variavel *op3, char operador, int linha);

#endif