#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macro para o tamanho da leitura das linhas
#define MAX 56

// Macro para o tamanho das strings de ação e posição, utilizadas no código
#define X 10

typedef struct livros livro;

typedef struct livros
{
    /*  Struct livros que possui:
        

        nome --> nome dos livros
        prox --> ponteiro para o próximo livro
        ant --> ponteiro para o livro anterior
        ultimo --> ponteiro para o ultimo livro da lista (todos os nós possuem 
                   essa informação)
        primeiro --> ponteiro para o primeiro livro da lista (todos os nós
                     possuem essa informação)
        
        *observação: o ultimo e primeiro serão guardados apenas para facilitar
                     a inserção.
    */

    char  *nome;

    livro *prox;

    livro *ant;

    livro *ultimo;

    livro *primeiro;

}livro;


// Adiciona livros em qualquer posição, seja ela no início, no fim, ou no meio
// da lista
livro *adicionar_livro(livro *ultimo_inserido, char posicao[]);


// nos casos em que não removemos o ultimo inserido, usamos essa função para
// remover o livro e realizar a conexão entre os nós que estavam ligados ao livro
void verifica_posicao_e_remove(livro *livro_descartado);


// função usada pra remover o livro que acabou de ser inserido, ou seja ele foi
// o último inserido
livro *remove_ultimo_inserido(livro *ultimo_inserido, char posicao[]);


// norteia a remoção do livro
livro *remover_livro(livro *ultimo_inserido, char posicao[]);


// realiza a impressão da lista de livros
void imprimir_livros(livro *ultimo_inserido);


// cria uma cabeça de lista para ajudar na inserção e remoção dos livros
livro *cria_cabeca_de_lista(livro *cabeca);


// libera a memória alocada para o armazenamento das informações sobre os livros
livro *libera_lista(livro *ultimo_livro);
