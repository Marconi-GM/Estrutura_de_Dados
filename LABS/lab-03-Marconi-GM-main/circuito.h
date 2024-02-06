#include <stdio.h>
#include <stdlib.h>


typedef struct circuitos{
    /*struct do tipo circuito.
      esse tipo possui três argumentos, o id do circuito, o número de jogadores
      do circuito e um vetor de inteiros com as jogadas de cada jogador no 
      circuito
    */
    
    int id_circuito;
    int n_jogadores;
    int *jogadas;

} circuito;


int soma_jogadas_jogador(int n_circuitos, int jogador, circuito V[]);

int calcula_circuito_dificil(circuito *circuitos, int qtde_circuitos);

void comeca_circuito(circuito *V, int j, int jogadores);
