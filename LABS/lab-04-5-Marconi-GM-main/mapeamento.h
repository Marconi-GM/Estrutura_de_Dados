#include <stdio.h>
#include <stdlib.h>

void gera_quadra(int **matriz, int N);

void preenche_subquadra(int **matriz, int N,
                        int **nova_matriz, int caso);

int **gera_subquadra(int **matriz, int N,
                    int linha_descartada, int coluna_descartada);

int soma_elementos(int **matriz, int N);

int **verifica_maior_urgencia(int **sub1, int **sub2, int **sub3, int **sub4,
                              int N);
                    
void imprime_matriz(int **matriz, int N);

void relatorio(int **subquadra, int N);

void desaloca_quadra(int **quadra, int N);

int  **verifica_area_critica(int **quadra, int N);

int verifica_segmentation_fault(int i, int j, int tamanho_matriz);

void altera_matriz(int i, int j, int novo_valor, int **matriz, int N);

void comeca_analise(int **quadra, int N, int alt);