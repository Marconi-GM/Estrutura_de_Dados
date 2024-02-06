#include "arvorerubronegra.h"

int eh_vermelho(arvore *arv)
{
    /*  Verifica se a cor do nó, da árvore, em questão é vermelho

        Retorna um inteiro, 0 em caso negativo e 1 em caso positivo 

        Parẫmetros:

        arv --> nó da arvore que se deseja verificar a cor
    */
    if(arv == NULL)
    {
        return 0;
    }

    return arv->cor == VERMELHO;
}


int eh_preto(arvore *arv)
{
    /*  Verifica se a cor do nó, da árvore, em questão é preto

        Retorna um inteiro, 0 em caso negativo e 1 em caso positivo 

        Parẫmetros:

        arv --> nó da arvore que se deseja verificar a cor
    */
    if(arv == NULL)
    {
        return 1;
    }

    return arv->cor == PRETO;
}


arvore *inserir_na_arvore(arvore *arv, variavel *var)
{
    /*  Insere um novo nó na árvore, já corrigindo caso a inserção desfaça as con
        dições necessárias para que a árvore seja uma ABB

        Para isso, verifica se a árvore é nula, se sim, cria um novo nó e o retorna,
        se não, verifica se o simbolo da variável é maior ou menor lexicograficamente
        em relação ao seu nó-pai para então inserir ou na esquerda ou na direita.

        se o simbolo for maior lexicograficamente, que o seu pai, insere-se na direita
        e na esquerda caso contrário

        retorna o novo nó

        Parâmetros:

        *arv --> do tipo arvore, arvore atual onde se deseja realizar a inserção
        *var --> do tipo variável, variável que se deseja inserir na árvore
    */
    arvore *nova;
    if(arv == NULL)
    {
        nova = malloc(sizeof(arvore));
        nova->esq = NULL;
        nova->dir = NULL;
        nova->var = var;
        nova->cor = VERMELHO;

        return nova;
    }

    else if(strcmp(var->simbolo, arv->var->simbolo) < 0)
    {
        arv->esq = inserir_na_arvore(arv->esq, var);
    }

    else
    {
        arv->dir = inserir_na_arvore(arv->dir, var);
    }

    arv = corrige_arvore(arv);

    return arv;
}


arvore *corrige_arvore(arvore *arv)
{
    /*  Corrige a árvore caso a mesma não estiver satisfazendo as condições para
        que seja considerada uma ABB.

        retorna a árvore, já corrigida

        Parâmetros:

        *arv --> do tipo arvore, arvore que se deseja corrigir, caso necessário
    */
    if(eh_vermelho(arv->dir) && eh_preto(arv->esq))
    {
        arv = rotaciona_p_esquerda(arv);
    }

    if(eh_vermelho(arv->esq) && eh_vermelho(arv->esq->esq))
    {
        arv = rotaciona_p_direita(arv);
    }

    if(eh_vermelho(arv->esq) && eh_vermelho(arv->dir))
    {
        sobe_vermelho(arv);
    }

    return arv;
}


arvore *rotaciona_p_esquerda(arvore *arv)
{
    /*  Rotacion a árvore para a esquerda

        Parâmetros:
        
        arv --> do tipo arvore, arvore que se deseja rotacionar para esquerda
    */
    arvore *aux;
    
    aux = arv->dir;
    arv->dir = aux->esq;
    aux->esq = arv;
    aux->cor = arv->cor;
    arv->cor = VERMELHO;

    return aux;
}


arvore *rotaciona_p_direita(arvore *arv)
{
    /*  Rotacion a árvore para a direita

        Parâmetros:
        
        arv --> do tipo arvore, arvore que se deseja rotacionar para direita
    */
    arvore *aux;

    aux = arv->esq;
    arv->esq = aux->dir;
    aux->dir = arv;
    aux->cor = arv->cor;
    arv->cor = VERMELHO;

    return aux;
}


void sobe_vermelho(arvore *arv)
{
    /*  Quando ambos os filhos do nó são vermelhos, a função os torna pretos e 
        sobe a cor vermelha para o pai

        Parâmetros:

        *arv --> do tipo arvore, arvore que se deseja corrigir as cores
    */
    arv->cor = VERMELHO;
    arv->esq->cor = PRETO;
    arv->dir->cor = PRETO;
}


void destroi_arvore(arvore *arv)
{
    /* Libera a memória alocada para uso da árvore

        Parâmetros:
    
        *arv --> do tipo arvore, arvore que se deseja liberar a memória alocada
    */
    if(arv != NULL)
    {
        destroi_arvore(arv->esq);
        destroi_arvore(arv->dir);

        free(arv->var);
        free(arv);
    }
}


void imprime_simbolos(arvore *arv)
{
    /*  Realiza a impressão dos símbolos da arvore, em ordem alfabética

        Parâmetros:

        *arv --> do tipo arvore, arvore que se deseja imprimir os símbolos
    */
    if(arv != NULL)
    {
        imprime_simbolos(arv->esq);

        printf("%s %s\n", arv->var->simbolo, arv->var->tipo);
        
        imprime_simbolos(arv->dir);
    }
}