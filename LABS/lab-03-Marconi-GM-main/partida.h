#include <stdio.h>
#include <stdlib.h>
#include "circuito.h"


typedef struct partidas{
    /*Struct do tipo partida
      esse tipo possui como argumentos: um float que será o valor do aluguel,
      o id da partida, o número de participantes, o número de circuitos, e um
      vetor do tipo circuitos, onde ficarão armazenadas as informações sobre 
      cada circuito
    */
   
    float valor_aluguel;
    int id_partida;
    int n_participantes;
    int n_circuitos;
    int n_equipamentos;
    circuito *v;

}partida;

float calcula_aluguel(int C, int E);

void relatorio_da_partida(int id, partida N[], circuito V[]);

void comeca_partida(int n_partidas);
