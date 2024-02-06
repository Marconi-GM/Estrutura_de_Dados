#include "mapeamento.h"


int main(void)
{
    int **quadra = NULL;
    int tamanho_matriz = 0;
    int alt = 0;


    scanf("%d", &tamanho_matriz);

    quadra =  malloc(tamanho_matriz * 2 * sizeof(int));
    gera_quadra(quadra, tamanho_matriz);

    scanf("%d", &alt);

    printf("Quadras:\n");
    imprime_matriz(quadra, tamanho_matriz);

    comeca_analise(quadra, tamanho_matriz, alt);

    return 0;
}
