#include <stdio.h>
#define MAX 300

typedef struct palavra{
    /* Tipo criado, em alternativa a um vetor de duas dimensões,
       para armazenas as palavras a serem buscadas.*/
    
    char nome[21];

}palavra;


void cria_documento(char matriz[][MAX], int linhas, int colunas)
{   
    /* Cria o documento a ser analisado.
       
       Parâmetros:
       matriz[][MAX] --> matriz de caracteres que será o nosso documento
       linhas --> quantidade de linhas de caracteres da matriz/documento
       colunas --> quantidade de caracteres por linha na matriz/documento*/

    int i = 0, 
        j = 0; // contadores

    for(i = 0; i < linhas; i++)
    {
        for(j = 0; j < colunas; j++)
        {
            scanf(" %c", &matriz[i][j]);
        }
    }
}


void recebe_palavras(palavra armazena_palavras[], int nmr_palavras)
{   
    /* Armazena as palavras que queremos procurar no documento.
       As palavras são armazenadas em um vetor do tipo ~palavra.
    
       Parâmetros:
       armazena_palavras[] --> vetor do tipo palavra, onde serão armazenadas
                               as palavras
       nrm_palavras--> inteiro correspondente ao número de palavras que 
                        queremos armazenar*/

    int i = 0;

    for(i = 0; i < nmr_palavras; i++)
    {
        scanf("%s", armazena_palavras[i].nome);
    }
}


int verifica_segmentation_fault(char documento[][MAX], 
                                int direcao, int x, int y, 
                                int ultima_linha, int ultima_coluna)
{   
    /* Verifica se a posição que queremos verificar na matriz/documento existe.
       Em caso positivo, retorna 1, caso contrário retorna 0.
       A função recebe uma direção para fazer a analise, ou seja, a direção na
       qual queremos saber se verificando a próxima posição da matriz naquela 
       direção dará segmentation fault.
       Defini as direções como: esquerda == 1, cima == 2, direita == 3,
       baixo == 4.
       Tentei passar uma string com o nome da direção, ex "esquerda" mas obtive
       erro ao tentar, então decidi por fazer dessa maneira.
       
       Parâmetros:
       
       documento[][MAX] --> matriz/documento na qual queremos verificar as
                            posições
       direção --> um inteiro, que representa uma direção. 1 para a esquerda, 2 
                    para cima, 3 para a direita e 4 para baixo.
       x e y --> inteiros representando a posição atual, na qual estamos na
                 matriz.
       ultima_linha e ultima_coluna --> o tamanho da matriz/documento, para
                                        realizar a verificação*/

    if(direcao == 1) //esquerda
    {
        if(y == 0)
        {
            return 0;
        }
        
        else
        {
            return 1;
        }
    }

    else if(direcao == 2) //cima    
    {
        if(x == 0)
        {
            return 0;
        }
        
        else
        {
            return 1;
        }
    }

    else if(direcao == 3) // direita
    {
        if(y == ultima_coluna - 1)
        {
            return 0;
        }
        
        else
        {
            return 1;
        }
    }

    else if(direcao == 4) // baixo
    {
        if(x == ultima_linha - 1)
        {
            return 0;
        }
        
        else
        {
            return 1;
        }
    }

    return 0;
}


int examina_palavra(char palavra_analisada[], char documento[][MAX],
                    int linhas, int colunas)
{
    /* A função verifica se a palavra em questão está no documento.
       Para isso ela recebe a palavra, e o documento, então percorre o documento
       até encontrar uma caracter que seja igual à primeira letra da palavra em
       questão.
       Uma vez encontrada as letras iguais, verifica-se se podemos tentar
       acessar as posições ao redor da letra encontrada.
       Nos casos em que se pode acessar, fazemos as verificações seguintes.
       Isto é, verificamos se a próxima letra da palavra em questão é igual a
       próxima letra no documento.
       Quando todas as letras são iguais, ou seja a palavra está no documento,
       retornamos 1, caso contrário retornamos 0.
       
       Parâmetros:
       
       palavra_analisada[] --> palavra que queremos encontrar no documento
       documento[][MAX] --> matriz/documento no qual procuraremos a palavra
       linhas e colunas --> o tamanho da matriz/documento */
    
    int i, j, k, x; //contadores
    int esquerda, cima, direita, baixo; //direções, as quais verificaremos se
                                        //podemos acessá-las

    char letra;
    
    letra = palavra_analisada[0]; //letra, inicialmente recebe a primeira letra
                                  //da palavra procurada
    for(i = 0; i < linhas; i++)
    {
        for(j = 0; j < colunas; j++)
        {
            letra = palavra_analisada[0]; //a cada iteração resetamos a letra para a primeira letra
                                          //da palavra, isto para evitar que a letra se perca caso uma
                                          //das procuras pare no meio.

            if(letra == documento[i][j]) //a primeira letra da palavra é igual a letra na posição 
            {                            //i j da matriz/documento
        
                esquerda = verifica_segmentation_fault(documento, 1, i, j, linhas, colunas);
                cima = verifica_segmentation_fault(documento, 2, i, j, linhas, colunas);
                direita = verifica_segmentation_fault(documento, 3, i, j, linhas, colunas);
                baixo = verifica_segmentation_fault(documento, 4, i, j, linhas, colunas);

                letra = palavra_analisada[0];
                if(esquerda == 1)
                {   
                    k = 1;
                    x = j - 1;

                    letra = palavra_analisada[k]; //A primeira letra já sabemos que é igual, agora
                                                  //verificaremos as seguintes (k)
                    while(((letra != '\0') && (letra == documento[i][x])) && (esquerda == 1))
                    {
                        esquerda = verifica_segmentation_fault(documento, 1, i, x, linhas, colunas); //verifica se ainda posso tentar acessar a posição
                        k += 1; //itera k para acessarmos a próxima letra da palavra procurada
                        x -= 1; //itera a posição na matriz para compararmos com a próxima letra da palavra
                        letra = palavra_analisada[k]; //atualiza letra para a próxima palavra, para a verificação no while
                    }

                    if(letra == '\0') //se todas as letras são iguais (a palavra está no documento)
                    {                 //então a variável letra tem como valor '\0'
                        return 1;
                    }
                }

                /*Análogo para todas as outras direções, com suas respectivas alterações*/
                
                letra = palavra_analisada[0];
                if(cima == 1)
                {   
                    k = 1;
                    x = i - 1;

                    letra = palavra_analisada[k];
                    while(((letra != '\0') && (letra == documento[x][j])) && (cima == 1))
                    {
                        cima = verifica_segmentation_fault(documento, 2, x, j, linhas, colunas);
                        k += 1;
                        x -= 1;
                        letra = palavra_analisada[k];
                    }
                    
                    if(letra == '\0')
                    {
                        return 1;
                    }
                }

                letra = palavra_analisada[0];
                if(direita == 1)
                {   
                    k = 1;
                    x = j + 1;

                    letra = palavra_analisada[k];
                    while(((letra != '\0') && (letra == documento[i][x])) && (direita == 1))
                    {
                        direita = verifica_segmentation_fault(documento, 3, i, x, linhas, colunas);
                        k += 1;
                        x += 1;
                        letra = palavra_analisada[k];
                    }
                    
                    if(letra == '\0')
                    {
                        return 1;
                    }
                }

                letra = palavra_analisada[0];
                if(baixo == 1)
                {  
                    k = 1;
                    x = i + 1;

                    letra = palavra_analisada[k];
                    while(((letra != '\0') && (letra == documento[x][j])) && (baixo == 1))
                    {
                        baixo = verifica_segmentation_fault(documento, 4, x, j, linhas, colunas);
                        k += 1;
                        x += 1;
                        letra = palavra_analisada[k];
                    }
                    
                    if(letra == '\0')
                    {
                        return 1;
                    }
                }
            }
        }
    }

    return 0; //caso a palavra não está na matriz/documento retorna 0
}


void verifica_palavras_no_documento(char documento[][MAX], 
                                    palavra armazena_palavras[MAX], 
                                    int N_palavras, int linhas, int colunas)
{   
    /* Verifica se as palavras que queremos encontrar estão no documento.
       A função recebe, praticamente, o documento e as palavras. Então,
       para cada palavra, ela chama a função examina_palavra e, caso a palavra
       esteja no documento, recebe como resposta 1, caso contrário recebe 0.
       
       Parâmetros:
       documento[][MAX] --> o documento de caracteres a ser analisado
       armazena_palavras --> o vetor do tipo palavra com todas as palavras a
                             serem buscadas
       N_palavras --> o número de palavras a serem buscadas
       linhas --> o número de linhas da matriz/documento
       colunas --> o número de colunas da matriz/documento */

    int i = 0,
        resposta = 0;

    for(i = 0; i < N_palavras; i++)
    {
        resposta = examina_palavra(armazena_palavras[i].nome, documento, linhas, colunas);
        if(resposta == 1)
        {
            printf("A palavra %s está no texto!\n\n", armazena_palavras[i].nome);
        }

        else if(resposta == 0)
        {
            printf("A palavra %s não está no texto!\n\n", armazena_palavras[i].nome);
        }
    }
}


int main(void)
{
    palavra armazena_palavras[MAX];

    char matriz_documento[MAX][MAX];

    int numero_linhas = 0,              // quantidade de linhas de caracteres
        qtde_caracteres = 0,            // quantidade de carecteres por linha
        nmr_palavras_desejadas = 0;     // quantas palavras queremos encontrar

    scanf("%d %d %d", &numero_linhas, &qtde_caracteres, &nmr_palavras_desejadas);

    cria_documento(matriz_documento, numero_linhas, qtde_caracteres);
    recebe_palavras(armazena_palavras, nmr_palavras_desejadas);
    verifica_palavras_no_documento(matriz_documento, armazena_palavras, nmr_palavras_desejadas, numero_linhas, qtde_caracteres);


    return 0;
}