#include "batmemory.h"


void verifica_memoria_alocada(bat_memoria *mem)
{
    /*  Verifica se há necessidade de reduzir o tamanho da memória alocada.
        A função verifica se há valores após o primeiro quarto da memória.
        Se sim, então não reduz, se não há valores, então reduz a memória alo
        cada pela metade.

        Parâmetros:
        
        *mem --> mem representa a nossa MEMoria, é um ponteiro para a struct do
                tipo bat_memoria.
    */
    int reduzir_metade = 1;
    int *vetor_auxiliar = NULL;
    int i = 0;
    
    // i começa no primeiro quarto
    i = mem->tamanho/4;

    for(i = mem->tamanho/4; i < mem->tamanho && reduzir_metade != 0; i++)
    {
        // Se após o primeiro quarto Há valores difentes de zero, ou seja,
        // há valores válidos na memória
        if(mem->bat_vetor[i] != 0)
        {
            // Então não precisa reduzir
            reduzir_metade = 0;
        }
    }

    // Se reduzir_metade não foi setado para zero, então não há valores após o
    // primeiro quarto e então reduz metade
    if(reduzir_metade)
    {
        vetor_auxiliar = malloc((mem->tamanho/2) * sizeof(int));
        for(int i = 0; i < (mem->tamanho/2); i++)
        {
            vetor_auxiliar[i] = mem->bat_vetor[i];
        }

        free(mem->bat_vetor);
        mem->bat_vetor = vetor_auxiliar;
        mem->tamanho /= 2;
    }
}


void guarda_lista_inteiros(bat_memoria *mem, int N, int posicao)
{
    /*  Guarda a lista de inteiros na memória.
        Para isso, a função recebe um N, que será o primeiro elemento do vetor,
        na memória, além da informação da quantiade de valores serão guaradados
        
        Parâmetros:
        
        *mem --> mem representa a nossa MEMoria, é um ponteiro para a struct do
                tipo bat_memoria.
        N --> inteiro, representa a quantidade de valores que serão guardados 
                na memória, é também o valor da primeira posição do vetor.
        posicao --> a posição válida da memória, na qual cabe um vetor de N 
                    elementos de forma contínua, do tipo inteiro.
    */
    int x;
    int k = 1;

    mem->bat_vetor[posicao] = N;
    mem->uso += (N + 1);

    for(int i = 0; i < N; i++)
    {
        scanf("%d", &x);
        mem->bat_vetor[posicao + k] = x;
        k += 1;
    }
}


bat_memoria *inicializa_memoria(bat_memoria *mem) 
{
    /*  Inicializa a memória do bat_pc

        Parâmetros:
        
        *mem --> mem representa a nossa MEMoria, é um ponteiro para a struct do
                tipo bat_memoria.
    */
    mem = malloc(sizeof(bat_memoria));
    mem->tamanho =  8;
    mem->uso = 0;

    mem->bat_vetor = malloc((mem->tamanho) * sizeof(int));

    for(int i = 0; i < mem->tamanho; i++)
    {
        // memória não utilizada, ou seja, o lixo, é representado pelo valor 0
        mem->bat_vetor[i] = 0;
    }

    return mem;
}


void dobra_tamanho_vetor(bat_memoria *mem)
{
    /*  Se o vetor está cheio, dobra-se o seu tamanho.
        Caso não haja memória contínua suficiente para armazenar o próximo vetor
        de N elementos, então dobra-se o tamanho do vetor, para que seja possível
        armazená-lo.

        Parâmetros:
        
        *mem --> mem representa a nossa MEMoria, é um ponteiro para a struct do
                tipo bat_memoria.
    */
    int *vetor_auxiliar = NULL;
    vetor_auxiliar = malloc((mem->tamanho * 2) * sizeof(int));
    
    for(int i = 0; i < (mem->tamanho * 2); i++)
    {
        if(i < (mem->tamanho))
        {
            vetor_auxiliar[i] = mem->bat_vetor[i];
        }

        else
        {
            vetor_auxiliar[i] = 0;
        }
    }

    free(mem->bat_vetor);
    mem->bat_vetor = vetor_auxiliar;
    mem->tamanho *= 2; 

}


int primeira_posicao_possivel_de_armazenar(bat_memoria *mem, int N)
{
    /*  Verifica a primeira posição da memória na qual é possível armazenar de 
        forma contínua um vetor de N elementos.
        
        Parâmetros:
        
        *mem --> mem representa a nossa MEMoria, é um ponteiro para a struct do
                tipo bat_memoria.
    */
    int contador = 0;

    for(int i = 0; i < mem->tamanho; i++)
    {
        // Se a posição não está sendo usada, então seu valor é 0
        if(mem->bat_vetor[i] == 0)
        {
            // contador até o tamanho do vetor que seja deseja armazenar mais o
            // primeiro valor, que no caso é o seu tamanho
            contador += 1;
            if(contador == N + 1)
            {
                // retorna a posição na qual é possível a inserção
                return (i - N);
            }
        }

        else
        {
            contador = 0;
        }
    }

    // se não há posição possível, retorna -1
    return -1;
}
