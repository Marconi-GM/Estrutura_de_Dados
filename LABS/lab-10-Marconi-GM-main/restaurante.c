#include "cozinha.h"
#include "maxheap.h"


void registra_sobreviventes(survivor *sobreviventes, int numero_sobreviventes)
{
    /*  Faz o registro dos sobreviventes e armazena seus dados
    
        A função recebe os dados de cada sobrevivente e os armazena em uma posi
        ção do vetor de sobreviventes.
    
        Parâmetros:

        *sobreviventes --> vetor de sobreviventes, do tipo tipo struct survivor
        numero_sobreviventes --> número de sobreviventes que se deseja realizar 
                                 o registro
    */
    for(int i = 0; i < numero_sobreviventes; i++)
    {
        scanf("%s ", sobreviventes[i].nome);
        scanf("%s ", sobreviventes[i].sobrenome);
        scanf("%d", &sobreviventes[i].dias_sobrevividos);

        // O ID dos sobreviventes e a sua posição da inserção no vetor
        sobreviventes[i].id = i;
    }
}


void pedidos_e_alteracoes(FP *fila, survivor *sobreviventes, int N)
{
    /*  Dado uma quantidade N de operações, seja ou o registro de um novo pedido
        ou a alteração da prioridade de um já existente, a função as realiza
        
        A função verifica qual operação deverá executar.
        Caso seja um registro de um novo pedido, chama uma função para isso.
        Caso seja a alteração de prioridade, chama uma função para isso.

        Parâmetros:
        
        *fila --> fila de prioridades, contém os pedidos e o número de pedidos
        *sobreviventes --> vetor de sobreviventes, contém seus dados
        N --> int, número de quantas operações deve se realizar na rodada
    */
    char operacao[OPERACAO];

    int id = 0;
    int valor = 0;

    for(int i = 0; i < N; i++)
    {
        scanf("%s", operacao);

        if(strcmp(operacao, "novo") == 0)
        {
            registra_pedido(fila, sobreviventes);
        }

        else if(strcmp(operacao, "altera") == 0)
        {
            scanf("%d %d", &id, &valor);
            altera_prioridade(fila, id, valor);
        }
    }
}


void entrega_de_pedidos(FP *fila, survivor *sobreviventes, int panelas)
{
    /*  Dado um número X de panelas, entrega X pedidos por rodada
    
        A função recebe o pedido pronto, que tem maior prioridade na fila
        e o "entrega"
        
        Parâmetros:
        
        *fila --> fila de prioridade, contém as informações os pedidos e a quan
                  tidade de pedidos (fila->n)

        *sobreviventes --> vetor de sobreviventes, contém seus dados

        panelas --> int, número de panelas da cozinha, ou seja, o número de 
                    pedidos que se consegue entregar por rodada
    */
    pedidos pedido_pronto;

    for(int i = 0; i < panelas && fila->n > 0; i++)
    {
        pedido_pronto = busca_pedido(fila);
        printf("%s ", sobreviventes[pedido_pronto.id].nome);
        printf("%s ", sobreviventes[pedido_pronto.id].sobrenome);
        printf("%s ", pedido_pronto.prato);
        printf("%d\n", pedido_pronto.prioridade);
    }
}


int rodadas(FP *fila, survivor *sobreviventes, int panelas)
{
    /*  Realiza a rodada, seja entregando pedidos ou recebendo novos/alterando

        Para isso a função lê a quantidade de operações que se realizará na
        rodada.
        Após isso, chama uma função para registrar os novos pedidos e alterações
        e logo depois entrega os pedidos já prontos.

        A função retorna o número da última rodada, isso para, quando não ter mais 
        novas operações, saber qual foi a última rodada que aconteceu e poder 
        continuar entregando os pratos restantes na fila
    
        Parâmetros:
        
        *fila --> fila de prioridade, contém as informações os pedidos e a quan
                  tidade de pedidos (fila->n)

        *sobreviventes --> vetor de sobreviventes, contém seus dados

        panelas --> int, número de panelas da cozinha, ou seja, o número de 
                    pedidos que se consegue entregar por rodada
    
    */
    int N;
    int n_rodada = 1;

    scanf("%d", &N);
    while(N != 0)
    {
        printf("---- rodada %d ----\n", n_rodada);
        pedidos_e_alteracoes(fila, sobreviventes, N);
        entrega_de_pedidos(fila, sobreviventes, panelas);

        n_rodada += 1;
        scanf("%d", &N);
    }

    return n_rodada;
}