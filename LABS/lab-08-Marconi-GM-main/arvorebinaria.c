#include "arvorebinaria.h"
#include "funcoes_expressoes.h"


arvore *cria_arvore(char expressao, arvore *esq, arvore *dir)
{
    /* Dada as subárvores direita e esquerda, cria uma nova árvore*/
    arvore *nova_arvore = NULL;

    nova_arvore = malloc(sizeof(arvore));
    nova_arvore->expressao = expressao;
    nova_arvore->dir = dir;
    nova_arvore->esq = esq;

    return nova_arvore;
}

arvore *monta_arvore(char expressao[])
{
    /* Dada uma expressão pós-fixa, monta uma arvore

        Para isso cria-se uma subarvore esquerda, depois uma subarvore direita
        para então criar uma árvore com essas subárvores.

        retorna a raiz da árvore montada.
        
        Parâmetros:
        
        expressão --> vetor de caracteres, contém uma expressão pósfixa*/
    arvore *esq = NULL, *dir = NULL;
    arvore *sub_arv_esq = NULL, *sub_arv_dir = NULL;

    for(int i = 0; expressao[i] != '\0'; i++)
    {
        // verifica se é numero ou varivável
        if(eh_inteiro(expressao[i]) || eh_variavel(expressao[i]))
        {
            // se for número, e se a arvore esquerda está livre
            if(esq == NULL)
            {   
                // então cria um arvore e armazena nessa arvore esquerda
                esq = cria_arvore(expressao[i], NULL, NULL);
            }

            // se a arvore esquerda já possui uma subarvore
            else if(dir == NULL)
            {
                // então agora armazena essa arvore na arvore direita
                dir = cria_arvore(expressao[i], NULL, NULL);
            }
        }

        // se o caractér for um operador
        else if(eh_operador(expressao[i]))
        {
            // e a subarvore está vazia
            if(sub_arv_esq == NULL)
            {   
                // entao cria essa subarvore e armazena na sub arvore esquerda
                sub_arv_esq = cria_arvore(expressao[i], esq, dir);
            }

            // se a sub arvore esquerda está cheia, então armazene na sub arvore direita
            else if(sub_arv_dir == NULL)
            {
                sub_arv_dir = cria_arvore(expressao[i], esq, dir);
            }

            else
            {
                // se as duas subarvores estão cheias, então crie uma arvore cuja
                // subavores serão a subarvore esquerda e a subarvore direita,
                // sendo a raiz um operador e armazena tudo isso na sub arvore esquerda
                sub_arv_esq = cria_arvore(expressao[i], sub_arv_esq, sub_arv_dir);

                //libera a subarvore direita para o futuro armazenamento das subarvores seguintes
                sub_arv_dir = NULL;
            }

            // libera as folhas esquerda e direitas para uso novamente para a criação de uma nova expressão
            esq = NULL;
            dir = NULL;
        }
    }

    // no final a raiz da árvore resultante ficará guardada na sub_arv_esq
    return sub_arv_esq;
}

void imprime_arvore(arvore *arv)
{
    /* Imprime a expressão em sua forma infixa
    
        Parâmetros:
        
        arv--> arvore que contém a expressão que se deseja imprimir
    */
    if(arv != NULL)
    {
        if(arv->esq != NULL && arv->dir != NULL)
        {
            printf("(");
        }

        imprime_arvore(arv->esq);

        // se for operador, imprime o operador com espaço atrás e na frente 
        // apenas para via de formatação
        if(eh_operador(arv->expressao))
        {
            printf(" %c ", arv->expressao);
        }

        else
        {
        printf("%c", arv->expressao);
        }

        imprime_arvore(arv->dir);

        if(arv->esq != NULL && arv->dir != NULL)
        {
            printf(")");
        }
    }

}


arvore *otimiza_arvore(arvore *arv)
{
    /*  Otimiza a árvore.

        A função funciona recursivamente.

        Primeiro ela caminha até as folhas da árvore. Uma vez nas folhas ela
        retorna a própria folha, dessa maneira as folhas (ou subarvores) ficam
        guardadas nas variáveis operando1 e operando2.

        Já com as folhas, ou subárvores, verifica-se se elas formam, junto com 
        o operador, uma expressão otimizável.

        Em caso positivo, chama-se outra função para relizar a otimização
        Em caso negativo, nada se faz, mantendo a árvore como ela está.

        Retorna a árvore otimizada.

        Parâmetros:

        arv --> arvore que se deseja otimizar.
    */
    arvore *operando1,
           *operando2;
    
    char operador;

    if(arv == NULL)
    {
        printf("ÁRVORE NULA\n");
    }

    else if(arv->esq == NULL && arv->dir == NULL)
    {
        return arv;
    }

    else
    {
        operando1 = otimiza_arvore(arv->esq);
        operando2 = otimiza_arvore(arv->dir);
        operador = arv->expressao;

        // Caso seja otimizavel
        if(eh_otimizavel(operador, operando1->expressao, operando2->expressao))
        {
            // então arv->expressao recebe T ou F
            arv->expressao = otimiza(operador, operando1->expressao, operando2->expressao);

            // libera-se a memória usada pelas subarvores
            destroi_arvore(arv->esq);
            destroi_arvore(arv->dir);

            // seta as subarvores para NULL para o funcionamento do programa
            arv->esq = NULL;
            arv->dir = NULL;
        }

        // caso contrário, as subarvores recebem elas mesmas, nada alterando
        // dessa maneira
        else
        {
            arv->esq = operando1;
            arv->dir = operando2;
        }
    }

    return arv;
}


void destroi_arvore(arvore *arv)
{
    /* Libera a memória alocada para uso da árvore.
        
        Para isso, verifica-se se arv é uma folha, caso contrário chama-se a 
        função recursivamente até que se encontra as folhas para, então, voltar
        liberando a memória usada.
        
        Parâmetros:
        
        arv --> arvore usada ao decorror do programa
    */
    if(arv->esq == NULL && arv->dir == NULL)
    {
        free(arv->esq);
        free(arv->dir);
        free(arv);
    }

    else
    {
        destroi_arvore(arv->esq);
        destroi_arvore(arv->dir);
        free(arv);
    }
}
