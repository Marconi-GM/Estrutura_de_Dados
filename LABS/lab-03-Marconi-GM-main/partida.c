#include "partida.h"


float calcula_aluguel(int C, int E)
{
    /* Calcula o aluguel da partida
       Retorna o alguel.
       
       Parâmetros:
       
       C --> inteiro, correspondente a quantidade de circuitos
       E --> inteiro, correspondente ao número de equipamentos alugados
    */
    float aluguel = 0;

    aluguel = (10 * C) + (17.5 * E);
    return aluguel;
}


void relatorio_da_partida(int id, partida N[], circuito V[])
{
    /* Formatação das informações para a saída do programa */
    int total_jogadas = 0,
        mais_dificil = 0;

    printf("Partida %d\n", id);

    printf("Num. de Jogadores: %d - ", N[id - 1].n_participantes);
    printf("Num. de Circuitos: %d - ", N[id - 1].n_circuitos);
    printf("Num. de Equipamentos: %d\n", N[id - 1].n_equipamentos );
    printf("Valor do Aluguel: R$ %.2f\n", N[id - 1].valor_aluguel);
    for(int i = 1; i <= N[id -1 ].n_participantes; i++)
    {
        total_jogadas = soma_jogadas_jogador(N[id - 1].n_circuitos, i - 1, V);
        printf("Jogador %d: %d\n", i, total_jogadas);
    }

    mais_dificil = calcula_circuito_dificil(V, N[id - 1].n_circuitos);
    printf("Circuito mais dificil: %d\n", mais_dificil);

    printf("##########\n");
}


void comeca_partida(int n_partidas)
{
    /* Realiza as partidas jogadas.
       Para isso a função recebe o número de partidas para logo em seguida,
       para cada partida, chamar a função comeca_circuito e realizar os circuitos
       da partida em questão.
       Após isso feito, chama-se o relatório da partida.

       Parâmetros:

       n_partidas --> inteiro correspondente ao número de partidas
       */
    int i = 0,
        j = 0,
        id_partida = 0;

    partida *N = NULL;
    circuito *V = NULL;

    N = malloc(n_partidas * sizeof(partida));
    for(i = 0; i < n_partidas; i++)
    {
        scanf("%d %d %d", &N[i].n_participantes, &N[i].n_circuitos, &N[i].n_equipamentos); // N[i] == *(N + i)
        N[i].valor_aluguel = calcula_aluguel(N[i].n_circuitos, N[i].n_equipamentos);
        
        V = malloc(sizeof(circuito) * N[i].n_circuitos);
        for(j = 0; j < N[i].n_circuitos; j++)
        {
            comeca_circuito(V, j, N[i].n_participantes);
        }
        
        id_partida = i + 1;
        relatorio_da_partida(id_partida, N, V);
        for(j = 0; j < N[i].n_circuitos; j++)
        {
            free(V[j].jogadas);
        }
        free(V);

    }
    free(N);
}
