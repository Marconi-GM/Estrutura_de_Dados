#include "batmemory.h"


int main(void)
{
    int n_instrucoes = 0;
    char instrucao[10];

    bat_memoria *memoria = NULL;
    memoria = inicializa_memoria(memoria);

    scanf("%d", &n_instrucoes);
    
    for(int i = 0; i < n_instrucoes; i++)
    {
        scanf("%s", instrucao);

        if(strcmp(instrucao, "bat-alloc") == 0)
        {
            bat_alloc(memoria);
        }

        else if(strcmp(instrucao, "bat-free") == 0)
        {
            bat_free(memoria);
        }

        else if(strcmp(instrucao, "bat-uso") == 0)
        {
            bat_uso(memoria);
        }

        else if(strcmp(instrucao, "bat-print") == 0)
        {
            bat_print(memoria);
        }
    }

    free(memoria->bat_vetor);
    free(memoria);


    return 0;
}
