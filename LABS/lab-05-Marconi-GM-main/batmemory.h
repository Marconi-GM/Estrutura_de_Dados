/* 
   No último lab, foi pedido que eu comentasse o header, mas fiquei em dúvida
   se eu devo comentar os dois arquivos ou só aqui. Na dúvida, farei breves 
   comentários aqui, sobre as funçõesm, e nos arquivos .c farei comentários mais
   comepletos.
   Valeeu!!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* struct que representa a bat_memoria
   Com três atributos:
   uso --> inteiro, representa quanto da 'memoria' está sendo utilizada de fato
   tamanho --> inteiro, representa quanto da 'memoria' foi alocada
   *bat_vetor --> um vetor de inteiros, representando a 'memoria'
*/
typedef struct vetor
{
    int uso;
    int tamanho;
    int *bat_vetor;

}bat_memoria;

// Aloca a memória e, logo em seguida, guarda os inteiros na memória
void bat_alloc(bat_memoria *mem);

// Verifica quanto da memória está em uso
void bat_uso(bat_memoria *mem);

// Printa um vetor de inteiros, dada sua posição de início na memória
void bat_print(bat_memoria *mem);

// Libera um espaço na memória para ser reutilizado e
void bat_free(bat_memoria *mem);

// inicializa a memória
bat_memoria *inicializa_memoria(bat_memoria *mem);

// dobra o tamanho do vetor, ou seja, da memória alocada
void dobra_tamanho_vetor(bat_memoria *mem);

// devolve a posição da qual é possível armazenar o vetor inteiro
int primeira_posicao_possivel_de_armazenar(bat_memoria *mem, int N);

// guarda a lista de inteiros na memória
void guarda_lista_inteiros(bat_memoria *mem, int N, int posicao);

// verifica se é necessário reduzir a quantidade de memória alocada
void verifica_memoria_alocada(bat_memoria *mem);
