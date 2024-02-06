#include "sistema.h"

int main(void)
{
    sistema *banco_de_dados;
    banco_de_dados = cria_sistema();

    char instrucao[15];
    char nome_familia[FAMILIA];
    char nome[CRIANCA], sobrenome[CRIANCA];
    
    int qtde_doces = 0;
    int qtde_casas = 0;

    scanf("%s", instrucao);

    while(strcmp(instrucao, "FINALIZAR") != 0)
    {
        if(strcmp(instrucao, "ENTRAR") == 0)
        {
            scanf("%s %d", nome_familia, &qtde_doces);
            inclui_familia(banco_de_dados, nome_familia, qtde_doces);
        }

        else if(strcmp(instrucao, "SAIR") == 0)
        {
            scanf("%s", nome_familia);
            remove_familia(banco_de_dados, nome_familia);
        }

        else if(strcmp(instrucao, "COMPRAR") == 0)
        {
            scanf("%s %d", nome_familia, &qtde_doces);
            atualiza_qtde_doces(banco_de_dados, nome_familia, qtde_doces);
        }

        else if(strcmp(instrucao, "TRICKORTREAT") == 0)
        {
            scanf("%s %s %d", nome, sobrenome, &qtde_casas);  
            trickortreat(banco_de_dados, nome, sobrenome, qtde_casas); 
        }


        scanf("%s", instrucao);
    }

    free(banco_de_dados);

    return 0;
}
