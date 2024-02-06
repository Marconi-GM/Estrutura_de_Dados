#include "partida.h"


int main(void)
{
    /*Corpo principal do programa.
      Aqui apenas recebo a quantidade de partidas e as envio para a função
      comeca_partida.
      Na função comeca_partida é que ocorrerá a execução das partidas.
    */

    int n_partidas = 0;

    scanf("%d", &n_partidas);
    comeca_partida(n_partidas);

    return 0;
}
