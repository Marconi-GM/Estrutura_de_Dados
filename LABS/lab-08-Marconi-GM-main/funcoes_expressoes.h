#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// verifica se o caracter é um operador 
int eh_operador(char x);

// verifica se o caracter é um inteiro
int eh_inteiro(char x);

// verifica se o caracter é uma variável
int eh_variavel(char x);

// otimiza expressões entre dois operandos e um operador para F ou T
char otimiza(char operador, char op1, char op2);

// verifica se a expressão entre dois operandos e o operador é otimizável
int eh_otimizavel(char operador, char operando1, char operando2);