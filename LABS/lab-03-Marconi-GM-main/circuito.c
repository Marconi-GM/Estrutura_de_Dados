#include "circuito.h"


int calcula_circuito_dificil(circuito *circuitos, int qtde_circuitos)
{
    /* Calcula o circuito mais difícil.
       Pra isso, adotamos o circuito mais díficil como o primeiro circuito,
       alocado na posição 0 do vetor de circuitos.
       Logo após, fazemos as comparações com a quantidade de jogadas necessárias
       pelos jogadores para completar o circuito.
       Se a quantidade de jogadas necessárias for maior que a quantidade de
       jogadas do primeiro circuito, atualiza-se as informações e assim
       sucessivamente.
       Retorna o id do circuito mais dificil.

       Parâmetros:

       *circuitos --> vetor do tipo circuito onde estão armazenadas todas as
                      informações sobre os circuitos jogados
        
        qtde_circuitos --> inteiro que representa a quantidade de circuitos
       */

    int i = 0,
        j = 0;

    int mais_dificil = circuitos[0].id_circuito;

    int soma_de_todas_jogadas = 0,
        soma_inicial = 0;

    for(i = 0; i < circuitos[0].n_jogadores; i++)
    {
        soma_inicial += circuitos[0].jogadas[i]; // Aqui calculamos a quantidade
    }                                            // de jogadas do primeiro circuito


    for(i = 1; i < qtde_circuitos; i++)
    {
        soma_de_todas_jogadas = 0;
        for(j = 0; j < circuitos[i].n_jogadores; j++)
        {
            soma_de_todas_jogadas += circuitos[i].jogadas[j]; // Aqui calcula-se a quantidade
        }                                                     // de jogadas dos próximos circuitos
        
        if(soma_de_todas_jogadas > soma_inicial) // Aqui atualiza-se as informações do
        {                                        // circuito mais dificil
            mais_dificil = circuitos[i].id_circuito;
            soma_inicial = soma_de_todas_jogadas;
        }

    }
    return mais_dificil;
}


int soma_jogadas_jogador(int n_circuitos, int jogador, circuito *V)
{
    /* Soma das jogadas de cada jogador na partida.
       Para isso, percorremos todos os circuitos e somamos as jogadas de cada
       jogador.
       Retorna o total de jogadas por jogador.
       
       Parâmetros:
       
       n_circuitos --> inteiro correspodente à quantidade de circuitos
       jogador --> inteiro correspondete ao jogador
       *V --> vetor do tipo circuito, onde estão guardados todas as informações
              sobre os circuitos jogados
    */
    int total_de_jogadas = 0;
    int i = 0;
    
    for(i = 0; i < n_circuitos; i++)
    {
        total_de_jogadas += V[i].jogadas[jogador];
    }
    
    return total_de_jogadas;
}


void comeca_circuito(circuito *V, int j, int jogadores)
{
    /* Realiza e guarda as informações de um único circuito.
       Para isso, lemos as informações do circuito e guardamos em um vetor
       de circuitos
       
       Parâmetros:
       
       *V --> vetor do tipo circuito, onde guardamos as informações do circuito
        j --> inteiro correspondente ao circuito jogado
        jogadores --> inteiro correspondente ao número de jogadores
    */
    int i = 0,
        k = 1;

    int *informacoes = NULL;

    V[j].jogadas = NULL;
    V[j].jogadas = malloc(sizeof(int) * jogadores);

    informacoes = malloc(sizeof(int) * (jogadores + 1));

    for(i = 0; i <= jogadores; i++)
    {   
        scanf("%d", &informacoes[i]);
    }


    V[j].n_jogadores = jogadores;
    V[j].id_circuito = informacoes[0];

    for(i = 0; i < jogadores; i++)
    {
        V[j].jogadas[i] = informacoes[k]; // k começa em 1, pois em informacoes[0]
        k += 1;                           // guardamos o id do circuito
    }

    free(informacoes);
}