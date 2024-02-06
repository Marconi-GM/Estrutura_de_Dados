#include "cozinha.h"
#include "maxheap.h"


int main(void)
{
    // fila de prioridade
    FP *fila;

    // array de sobreviventes
    survivor *sobreviventes;

    int panelas;
    int numero_sobreviventes;
    int n_rodadas = 0;

    scanf("%d %d", &panelas, &numero_sobreviventes);

    sobreviventes = malloc(numero_sobreviventes * sizeof(survivor));
    registra_sobreviventes(sobreviventes, numero_sobreviventes);

    fila = cria_fila(numero_sobreviventes);

    n_rodadas = rodadas(fila, sobreviventes, panelas);

    while(fila-> n != 0)
    {
        printf("---- rodada %d ----\n", n_rodadas);
        entrega_de_pedidos(fila, sobreviventes, panelas);

        n_rodadas += 1;
    }

    free(fila->pedido);
    free(fila);
    free(sobreviventes);

    return 0;
}
