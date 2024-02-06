/* Os comentários principais estão nas funções, no header .h apenas comentários
   breves. */
#include "livros.h"


int main(void)
{
    char  acao[X],
          posicao[X];
    
    livro *ultimo_inserido = NULL,
          *cabeca = NULL;

    ultimo_inserido = malloc(sizeof(livro));
    ultimo_inserido->nome = malloc(MAX * sizeof(char));

    ultimo_inserido = cria_cabeca_de_lista(ultimo_inserido);
    
    strcpy(posicao, "padrao");

    while(scanf(" %s ", acao) != EOF)
    {

        if(strcmp(acao, "adicionar") == 0)
        {
            strcpy(posicao, "padrao");
            ultimo_inserido = adicionar_livro(ultimo_inserido, "padrao");
        }

        else if(strcmp(acao, "remover") == 0)
        {
            ultimo_inserido = remover_livro(ultimo_inserido, posicao);
            strcpy(posicao, "padrao");

        }

        else if(strcmp(acao, "imprimir") == 0)
        {
            imprimir_livros(ultimo_inserido);
        }

        else if(strcmp(acao, "final") == 0)
        {
            scanf(" %s ", acao);
            ultimo_inserido = adicionar_livro(ultimo_inserido, "final");
            strcpy(posicao, "final");
        }

        else if(strcmp(acao, "inicio") == 0)
        {
            scanf(" %s ", acao);
            ultimo_inserido = adicionar_livro(ultimo_inserido, "inicio");
            strcpy(posicao, "inicio");
        }
    }


    cabeca = libera_lista(ultimo_inserido->ultimo);
    free(cabeca->nome);
    free(cabeca);
    

    return 0;
}
