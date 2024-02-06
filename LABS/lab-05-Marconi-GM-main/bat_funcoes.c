#include "batmemory.h"


void bat_free(bat_memoria *mem)
{
    /*  Libera uma repartição da memória para ser reutilizada.
        A função escaneia a posição na qual está guardada a quantidade de
        valores da repartição/vetor. E após isso libera a memória para ser 
        reutilizada.
        Após a liberação ela chama a outra função para verificar se é necessário
        a redução do tamanho da memória alocada.
        
        Parâmetros:
        
        *mem --> mem representa a nossa MEMoria, é um ponteiro para a struct do
                tipo bat_memoria.
    */
    int posicao = 0,
        inicio = 0,
        fim = 0,
        qtde = 0;

    scanf("%d", &posicao);
    
    // quantiade de valores no vetor, essa informação fica guardada em
    // mem->bat_vetor[posicao]
    qtde = mem->bat_vetor[posicao];

    // posição inicial, onde começará a liberação da memória
    inicio = posicao;

    // posição final, onde terminará a liberação da memória
    fim = posicao + mem->bat_vetor[posicao];

    for(int i = 0; i < mem->tamanho; i++)
    {
        if(i >= inicio && i <= fim)
        {
            mem->bat_vetor[i] = 0;
        }
    }

    // atualiza a quantidade de memória em uso
    mem->uso -= (qtde + 1);
    verifica_memoria_alocada(mem);
}


void bat_uso(bat_memoria *mem)
{
    /*  Verifica a quantidade de memória em uso em relação à quantiade alocada
    
        Parâmetros:
        
        *mem --> mem representa a nossa MEMoria, é um ponteiro para a struct do
                tipo bat_memoria.
    */
    printf("%d de %d\n", mem->uso, mem->tamanho);
}


void bat_print(bat_memoria *mem)
{
    /*  A função printa um vetor que está guardado na memória.
        Para isso, escaneia a posição na qual se guarda o inicio do vetor e a
        quantidade de valores nele contido.
        Após isso realiza a impressão.

        Parâmetros:
        
        *mem --> mem representa a nossa MEMoria, é um ponteiro para a struct do
                tipo bat_memoria.
    */
    int posicao = 0;
    int tamanho_vetor = 0;

    scanf("%d", &posicao);
    tamanho_vetor = mem->bat_vetor[posicao];

    for(int i = 1; i <= tamanho_vetor; i++)
    {
        if(i < tamanho_vetor)
        {
            printf("%d ", mem->bat_vetor[posicao + i]);
        }

        else
        {
            printf("%d", mem->bat_vetor[posicao + i]);
        }
    }

    printf("\n");
}


void bat_alloc(bat_memoria *mem)
{
    /*  A função verifica se há espaço na memória suficiente. Se sim, guarda a
        lista de inteiros na memória, se não, dobra o tamanho do vetor e então
        guarda a lista de inteiros na memória.
        
        Parâmetros:
        
        *mem --> mem representa a nossa MEMoria, é um ponteiro para a struct do
                tipo bat_memoria.
    */
    int posicao = 0;
    int N = 0;
    
    scanf("%d", &N);

    posicao = primeira_posicao_possivel_de_armazenar(mem, N);

    if(posicao == -1)
    {
        dobra_tamanho_vetor(mem);
        posicao = primeira_posicao_possivel_de_armazenar(mem, N);
    }

    guarda_lista_inteiros(mem, N, posicao);

    printf("%d\n", posicao);
}
