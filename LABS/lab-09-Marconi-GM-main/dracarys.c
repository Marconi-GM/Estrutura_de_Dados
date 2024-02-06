#include "dracarys.h"
#include "johncc.h"
#include "arvorerubronegra.h"

int main(void)
{
    variavel *var = NULL;

    arvore *raiz = NULL;

    char *linha;
    linha = malloc(MAX * sizeof(char));

    // representa o número da linha que foi lida no arquivo
    int numero_da_linha = 1;

    int *ha_erros;

    ha_erros = malloc(sizeof(int));
    *ha_erros = 0;


    while(fgets(linha, 200, stdin) != NULL)
    {
        // verifica se há parenteses na linha
        if(tem_parenteses(linha))
        {
            // caso tenha apenas atualiza o número da linha
            numero_da_linha += 1;
        }

        // verifica se a linha começa com letra
        else if( !comeca_com_letra(linha) )
        {
            numero_da_linha += 1;
        }

        // verifica se a linha começa com int, double, ou char
        else if(eh_declaracao(linha))
        {
            // em casos positivos, cria-se a variável
            var = cria_variavel(linha);

            // e a insere na árvore
            raiz = inserir_na_arvore(raiz, var);
            
            numero_da_linha += 1;
        }

        // caso não caia nos casos anteriores, é uma expressão
        else
        {
            // verifica se a linha é uma expressão válida
            verifica_expressao(linha, raiz, numero_da_linha, ha_erros);
            
            numero_da_linha += 1;
        }       
    }

    // caso haja erros durante a execução, *ha_erros recebera 1, caso contrário
    // continuará em 0, e logo não há erros de tipo
    if(*ha_erros == 0)
    {
        printf("Não há erros de tipo.\n");     
    }

    imprime_simbolos(raiz);

    destroi_arvore(raiz);
    free(linha);
    free(ha_erros);

    return 0;
}
