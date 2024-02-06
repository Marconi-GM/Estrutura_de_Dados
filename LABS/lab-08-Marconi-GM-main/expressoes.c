#include "expressoes.h"
#include "funcoes_expressoes.h"
#include "arvorebinaria.h"

#define MAX 100

int main(void)
{
    int numero_expressoes = 0;
    
    char expressao[MAX];

    arvore *arvore_montada,
           *arvore_otimizada;

    scanf("%d", &numero_expressoes);

    for(int i = 0; i < numero_expressoes; i++)
    {
        scanf("%s", expressao);

        arvore_montada = monta_arvore(expressao);
        imprime_arvore(arvore_montada);

        printf("\n");

        arvore_otimizada = otimiza_arvore(arvore_montada);
        imprime_arvore(arvore_otimizada);

        printf("\n");
        printf("\n");

        destroi_arvore(arvore_otimizada);
    }

    return 0;
}
