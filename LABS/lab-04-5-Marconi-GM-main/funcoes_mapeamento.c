#include "mapeamento.h"


void gera_quadra(int **matriz, int N)
{
    /* Gera a quadra principal do programa.
       A partir dela serão geradas subquadras e dessas mais subquadras e assim
       sucessivamente.
       
       Parâmetros:
       
       matriz --> ponteiro para ponteiro, do tipo inteiro, que representará a
                  matriz
       N --> inteiro, representa o tamanho da matriz quadrada, no caso a quadra
    */

    for(int i = 0; i < N; i++)
    {
        matriz[i] = malloc(N * sizeof(int));
    }

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
    }
}


void preenche_subquadra(int **matriz, int N,
                        int **nova_matriz, int caso)
{
    /* Preenche a subquadra com os elementos da 'matriz-mãe'.
       A função recebe a matriz-mãe, da qual será gerada a subquadra, além de 
       receber a nova matriz, ou seja a subquadra, o tamanho da matriz mãe, do 
       qual obteremos o tamanho da nova matriz e o caso.
       O caso representa a linha e a coluna removidas para a geração da
       submatriz.
       O caso == 1 representa uma submatriz, gerada desconsiderando-se a
       primeira linha e a primeira coluna da matriz-mãe.
       O caso == 2 representa uma submatriz, essa sem a primeira linha e ultima
       coluna da matriz-mãe.
       O caso == 3 representa uma submatriz, essa sem a ultima linha e a
       primeria coluna da matriz-mãe.
       O caso == 4 representa uma submatriz, essa sem a ultima linha e ultima 
       coluna da matriz-mae
       
       Parâmetros:
       
       matriz --> matriz da qual será gerada a submatriz, to tipo ponteiro para
                  ponteiro, de inteiros

       N --> o tamanho da matriz da qual será gerada a submatriz, inteiro.

       nova_matriz --> a submatriz gerada a ser preecnhida, do tipo ponteiro
                       para ponteiro, de inteiros.

       caso --> inteiro, que representa a situação a ser considerada.

       */
    int x = 0,
        y = 0;

    if(caso == 1)
    {
        x = 1;
        for(int i = 0; i < N - 1; i++) // N - 1 é o tamahno da nova matriz
        {
            y = 1;
            for(int j = 0; j < N - 1; j++)
            {
                nova_matriz[i][j] = matriz[x][y];
                y++;
            }
            x++;
        }
    }

    else if(caso == 2)
    {
        x = 1;
        for(int i = 0; i < N - 1; i++)
        {
            y = 0;
            for(int j = 0; j < N - 1; j++)
            {
                nova_matriz[i][j] = matriz[x][y];
                y++;
            }
            x++;
        }
    }

    else if(caso == 3)
    {
        x = 0;
        for(int i = 0; i < N - 1; i++)
        {
            y = 1;
            for(int j = 0; j < N - 1; j++)
            {
                nova_matriz[i][j] = matriz[x][y];
                y++;
            }
            x++;
        }
    }

    else if(caso == 4)
    {
        x = 0;
        for(int i = 0; i < N - 1; i++)
        {
            y = 0;
            for(int j = 0; j < N - 1; j++)
            {
                nova_matriz[i][j] = matriz[x][y];
                y++;
            }
            x++;
        }
    }
}


int **gera_subquadra(int **matriz, int N,
                    int linha_descartada, int coluna_descartada)
{
    /* Gera a subquadra levando em consideração qual linha e coluna descartar.
    
       Para isso, a função aloca a memória a ser utilizada e, dependendo de 
       qual coluna e qual linha serão descartadas, chama outra função para 
       preencher a subquadra.

       A função retorna o endereço da subquadra gerada
       
       Parâmetros:
       
       matriz --> matriz da qual será gerada as subquadras, do tipo ponteiro
                  para ponteiro de inteiros.
       
       N --> inteiro, representa o tamanho da matriz da qual será gerada as 
             subquadras.
        
       linha_descartada --> inteiro, representa a linha que não será levada em
                            conta na criação da subquadra.
                            
       coluna_descartada --> inteiro, representa a coluna que não será levada em
                             conta na criação da subquadra.
    */
    int **nova_matriz = NULL;

    nova_matriz = malloc((N - 1) * 2 * sizeof(int));
    for(int i = 0; i < N - 1; i++)
    {
        nova_matriz[i] = malloc((N - 1) * sizeof(int));
    }

    if(linha_descartada == 0)
    {
        if(coluna_descartada == 0)
        {
            preenche_subquadra(matriz, N, nova_matriz, 1);
        }

        else if(coluna_descartada == N -1)
        {
            preenche_subquadra(matriz, N, nova_matriz, 2);
        }
    }

    else if(linha_descartada == N -1)
    {
        if(coluna_descartada == 0)
        {
            preenche_subquadra(matriz, N, nova_matriz, 3);
        }

        else if(coluna_descartada == N -1)
        {
            preenche_subquadra(matriz, N, nova_matriz, 4);
        }
    }


    return nova_matriz;
}


int soma_elementos(int **matriz, int N)
{
    int soma = 0;
    int i = 0,
        j = 0;

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            soma += matriz[i][j];
        }
    }

    return soma;
}


int **verifica_maior_urgencia(int **sub1, int **sub2, int **sub3, int **sub4, int N)
{
    /* Verifica e retorna a subquadra de maior urgência.
       
       Aqui abro mão da impessoalidade nos comentários para já dizer que:
       a função ta ó, uma tuia.
       Me deparei com essas gambiarras quando percebi que, na minha lógica,
       cada subquadra gerada me daria um inteiro, e para comparar manualmente 
       esses quatro inteiros seria pior ainda.
       O problema é que esses quatro valores não foram criados em um vetor, onde
       seriam facilmente comparados, apenas são criados individualmente e
       armazenados em suas variáveis.
       Sei que a função está longe de ser aceitável e que da pra arrumar, 
       pórem são 00:52 de uma sexta feira, a prova de algebra linear é na terça
       e eu não estudei nada rsrsrs, então vou entregar essa versão do lab dessa
       maneira, pois vou usar o final de semanada pra estudar pra prova,
       e na próxima versão eu tento arrumar.
       Tmj demais leitor, você é fera!!
       
       A função recebe em quatro variáveis a soma dos elementos de quadra sub
       quadra, depois as coloca em um vetor para facilitar a comparação do maior
       valor.
       Uma vez o maior valor encontrado, guarda-se o indice que contem a infor
       mação de qual subquadra é a de maior urgência.
       Após isso, verifica-se qual índice foi guardado por último e retonra a
       subquadra correspondente.
       
       A função retorna o endereço da subquadra de maior urgência.
        
       Parâmetros:
       
       subx --> (x = 1, 2, 3, 4) são as subquadras geradas, das quais se somará
                os elementos.
                
       N --> inteiro, representa o tamanho das subquadras. 
       */
    int soma1 = 0,
        soma2 = 0,
        soma3 = 0,
        soma4 = 0;

    int *somas = NULL;

    int maior_soma = 0,
        indice = 0;

    somas = malloc(4 * sizeof(int));

    soma1 = soma_elementos(sub1, N);
    soma2 = soma_elementos(sub2, N);
    soma3 = soma_elementos(sub3, N);
    soma4 = soma_elementos(sub4, N);

    somas[0] = soma1;
    somas[1] = soma2;
    somas[2] = soma3;
    somas[3] = soma4;

    maior_soma = somas[0];
    for(int i = 1; i < 4; i++)
    {
        if(somas[i] > maior_soma)
        {
            maior_soma = somas[i];
            indice = i;
        }
    }

    free(somas);

    if(indice == 1)
    {
        return sub2;
    }

    else if(indice == 2)
    {
        return sub3;
    }

    else if(indice == 3)
    {
        return sub4;
    }


    return sub1;
}


void imprime_matriz(int **matriz, int N)
{
    /* Função imprime a matriz formatada.
    
       Parâmetros:
       
       matriz --> a matriz a ser imprimida.
       
       N --> o tamanho da matriz a ser imprimida, inteiro.
    */
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(j == N - 1)
            {
                printf("%d", matriz[i][j]);
            }

            else
            {
                printf("%d\t", matriz[i][j]);
            }
        }

        printf("\n");
    }
}


void relatorio(int **subquadra, int N)
{
    /* Cria o relatório de quais conjuntos precisam de atenção
    
    Parâmetros:
    
    subquadra --> a subquadra a ser impressa
    
    N --> tamanho da subquadra, inteiro
    */
    printf("\n");
    printf("Conjuntos que precisam de atenção:\n");
    imprime_matriz(subquadra, N);
}


void desaloca_quadra(int **quadra, int N)
{
    /* Desaloca as quadras criadas durante a execução do programa
    
    Parâmetros:
    
    quadra --> quadra a ser desalocada
    
    N --> inteiro, tamanho da quadra*/
    for(int i = 0; i < N; i++)
    {
        free(quadra[i]);
    }
    
    free(quadra);
}


int  **verifica_area_critica(int **quadra, int N)
{
    /* Verifica a area critica, de maior urgência.
    
    A função cria as subquadras a serem analisadas e verifica qual é a subquadra
    de maior urgência.
    
    retorna o endereço da subquadra de maior urgência.
    
    Parâmetros:
    
    quadra --> quadra das quais serão geradas as subquadras analisadas.
    
    N --> tamanho da subquadra.
    */
    int **sub_quadra1 = NULL,
        **sub_quadra2 = NULL,
        **sub_quadra3 = NULL,
        **sub_quadra4 = NULL;

    int **maior_urgencia = NULL;

    sub_quadra1 = gera_subquadra(quadra, N, 0, 0);
    sub_quadra2 = gera_subquadra(quadra, N, 0, N - 1);
    sub_quadra3 = gera_subquadra(quadra, N, N - 1, 0);
    sub_quadra4 = gera_subquadra(quadra, N, N - 1, N -1);

    maior_urgencia = verifica_maior_urgencia(sub_quadra1, sub_quadra2, sub_quadra3, sub_quadra4, N - 1);
    relatorio(maior_urgencia, N - 1);

    return maior_urgencia;

}


int verifica_segmentation_fault(int i, int j, int tamanho_matriz)
{
    /* Verifica se a posição que se tenta acessar existe.
    
       Em caso positivo retorna 1, em caso negativo retorna 0
       
       Parâmetros:
       
       i, j --> inteiros, representam a posição a ser acessada.
       tamanho_matriz --> representa o tamanho da matriz (AVA)*/
    if(i < 0)
    {
        return 0;
    }

    else if(j > tamanho_matriz - 1)
    {
        return 0;
    }

    return 1;
}


void altera_matriz(int i, int j, int novo_valor, int **matriz, int N)
{
    /* Verifica se é possível acessar a posição desejada e em caso positivo, 
       realiza a troca dos valores, alterando a matriz.
       
       Parâmetros:
       
       i, j --> posição que se deseja realizar a alteração
       novo_valor --> valor que se deseja atualizar.
       matriz --> a matriz na qual será realizada a alteração.
       N --> inteiro, representa o tamanho da matriz
       */
    int alteracao_valida = 1;

    alteracao_valida = verifica_segmentation_fault(i, j, N);

    if(alteracao_valida == 1)
    {
        matriz[i][j] = novo_valor;
    }

    else
    {
        printf("Posicao inexistente na matriz\n");
        exit(1);
    }

}


void comeca_analise(int **quadra, int N, int alt)
{
    /* A função começa a verificação da urgência de atendimento das quadras.
    
       Para isso, primeiro verifica a primeira ocorrência de area critica, para
       depois entrar em um While do qual só sairá se: 
       o usuário desejar (alt != 1) ou a dimensão da pŕoxima matriz for 1x1.
       
       Uma vez dentro do while, se recebe as informações relativas à posição 
       que se deseja alterar e o novo valor que nela será posto.
       
       Uma vez alterada a matriz, uma nova análise de area critica é feita e
       apos isso, atualiza-se a dimensão e verifica-se as condições novamente.
       
       Parâmetros:
       
       quadra --> quadra a ser analisada
       N --> inteiro, tamanho da quadra
       alt --> inteiro, onde se armazena a informação do desejo, ou não, de se
               alterar a quadra.
    */
    int **area_critica = NULL;

    int i = 0,
        j = 0,
        novo_valor = 0,
        dimensao = 0;
    
    area_critica = verifica_area_critica(quadra, N);
    desaloca_quadra(quadra, N);

    dimensao = N -1;

    

    while(alt == 1 && dimensao > 1)
    {
        scanf("%d %d %d", &i, &j, &novo_valor);
        altera_matriz(i, j, novo_valor, area_critica, dimensao);
        area_critica = verifica_area_critica(area_critica, dimensao);
        dimensao -= 1;
        if(dimensao > 1)
        {
            scanf("%d", &alt);
        }
    }
    desaloca_quadra(area_critica, dimensao);
}