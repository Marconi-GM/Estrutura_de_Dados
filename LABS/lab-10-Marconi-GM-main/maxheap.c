#include "maxheap.h"


FP *cria_fila(int tamanho)
{
    /*  Cria a fila de pedidos, uma fila de prioridade, na qual o maior tamanho
        possível é o número de sobreviventes
        
        A função aloca a memória para a fila de prioridade e então aloca a
        memória para o vetor de pedidos.
        
        Inicializa, também, a quantidade de pedidos armazenados na fila, n
        
        Parâmetros:
        
        tamanho --> int, tamanho do vetor de pedidos
    */
    FP *nova_fila;

    nova_fila = malloc(sizeof(FP));
    nova_fila->pedido = malloc(tamanho * sizeof(pedidos));
    nova_fila->n = 0;

    return nova_fila;
}


void troca(pedidos *a, pedidos *b)
{
    /* Troca dois pedidos de posição na fila de prioridade

        Parâmetros:

        *a, *b --> pedidos que terão suas posições trocadas
    */
    pedidos aux;
    
    aux = *a;
    *a = *b;
    *b = aux;
}

void registra_pedido(FP *fila, survivor *sobrevivente)
{
    /* Registra um novo pedido e o armazena na fila de prioridade
    
        Para isso, a função lê as informações dos pedidos e as armazena na
        ultima posição da fila, e se necessário, organiza a fila chamando a função
        sobe_no_heap()

        Parâmetros:

        *fila --> fila de prioridade, contém as informações os pedidos e a quan
                  tidade de pedidos (fila->n)

        *sobreviventes --> vetor de sobreviventes, contém seus dados
    */
    int ID;
    char prato[TAM_PRATO];

    scanf("%d", &ID);
    fgets(prato, TAM_PRATO, stdin);
    // retira o \n do final do nome do prato
    prato[strlen(prato) - 1] = '\0';

    // o id do pedido é o mesmo id do sobrevivente que realizou o pedido
    fila->pedido[fila->n].id = ID;

    // a prioridade do pedido, inicialmente, é o número de dias sobrevividos
    // do sobrevivente que fez o pedido (e logo tem ID igual ao ID do pedido)
    fila->pedido[fila->n].prioridade = sobrevivente[ID].dias_sobrevividos;
    strcpy(fila->pedido[fila->n].prato, prato);

    fila->n += 1;
    sobe_no_heap(fila, fila->n - 1);
}

void sobe_no_heap(FP *fila, int posicao_na_fila)
{
    /* Sobe um pedido na fila de prioridades, dado sua posição na fila
    
        Uma vez que a posição na fila, do pedido atual, é maior que zero e 
        sua prioridade é maior que a prioridade do seu 'pai' na fila, realiza-se
        a troca

        Parâmetros:

        *fila --> fila de prioridade, contém as informações os pedidos e a quan
                  tidade de pedidos (fila->n)

        posição_na_fila --> int, a posição do pedido atual na fila
    */
    if(posicao_na_fila > 0 && fila->pedido[PAI(posicao_na_fila)].prioridade < fila->pedido[posicao_na_fila].prioridade)
    {
        troca(&fila->pedido[posicao_na_fila], &fila->pedido[PAI(posicao_na_fila)]);
        sobe_no_heap(fila, PAI(posicao_na_fila));
    }
}

pedidos busca_pedido(FP *fila)
{
    /*  Busca o pedido de maior prioridade, e o retorna para ser entregue
    
        Parâmetros:

        *fila --> fila de prioridade, contém as informações os pedidos e a quan
                  tidade de pedidos (fila->n)
    */
    pedidos pedido_pronto;
    
    pedido_pronto = fila->pedido[0];
    troca(&fila->pedido[0], &fila->pedido[fila->n - 1]);
    
    fila->n -= 1;
    desce_no_heap(fila, 0);

    return pedido_pronto;
}

void desce_no_heap(FP *fila, int posicao_na_fila)
{
    /*  Dada uma posição na fila, verifica se é necessário arrumar a fila de 
        prioridades

        Parâmetros:

        *fila --> fila de prioridade, contém as informações os pedidos e a quan
                  tidade de pedidos (fila->n)

        posição_na_fila --> int, a posição do pedido atual na fila    
    */
    int maior_filho;

    maior_filho = F_ESQ(posicao_na_fila);
    if(F_ESQ(posicao_na_fila) < fila->n)
    {
        if(F_DIR(posicao_na_fila) < fila->n && 
            fila->pedido[F_ESQ(posicao_na_fila)].prioridade < fila->pedido[F_DIR(posicao_na_fila)].prioridade)
        {
            maior_filho = F_DIR(posicao_na_fila);
        }

        if(fila->pedido[posicao_na_fila].prioridade < fila->pedido[maior_filho].prioridade)
        {
            troca(&fila->pedido[posicao_na_fila], &fila->pedido[maior_filho]);
            desce_no_heap(fila, maior_filho);
        }
    }
}

void altera_prioridade(FP *fila, int id, int valor)
{
    /* Altera a prioridade de um pedido já existente
    
        A função realiza a busca, no vetor de pedidos, do pedido com o id == ID
        e então atualiza sua prioridade
        Após isso concerta a fila com os valores novos de prioridade

        Parâmetros:

        *fila --> fila de prioridade, contém as informações os pedidos e a quan
                  tidade de pedidos (fila->n)

        id --> int, ID do pedido que se deseja altera a prioridade. Também é o 
               ID do sobrevivente que fez o pedido
        
        valor --> int, valor ao qual se somará à prioridade atual.
    */
    int pedido_encontrado = 0;
    if(valor >= 0)
    {
        for(int i = 0; (!pedido_encontrado); i++)
        {
            if(fila->pedido[i].id == id)
            {
                fila->pedido[i].prioridade += valor;
                // Como o valor é positivo, sobe-se no heap 
                sobe_no_heap(fila, i);

                pedido_encontrado = 1;
            }
        }

    }

    else if(valor < 0)
    {
        for(int i = 0; (!pedido_encontrado); i++)
        {
            if(fila->pedido[i].id == id)
            {
                fila->pedido[i].prioridade += valor;
                // como o valor é negativo, desce-se no heap
                desce_no_heap(fila, i);

                pedido_encontrado = 1;
            }
        }
    }
}
