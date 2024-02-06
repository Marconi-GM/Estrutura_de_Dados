#include <stdio.h>


void pix_recebidos(int PIX[], int n)
{   
    int i;
    for(i = 0; i < n; i++)
    {
        scanf("%d", &PIX[i]);
    }
}


int qtde_de_cada_tipo(int PIX[], int n, int tipo)
{
    int qtde = 0, i;
    for(i = 0; i < n; i++)
    {
        if(PIX[i] == tipo)
        {
            qtde++;
        }
    }

    return qtde;
}


void maior_sequencia_e_tipo(int PIX[], int n, int maior_e_tipo[])
{
    int i,
        contador = 1, 
        tamanho_sequencia = 1,
        tipo_do_pix = PIX[0];

    for(i = 1; i <= n; i++)
    {
        if(i < n && PIX[i] == PIX[i - 1])
        {
            contador += 1;
            if(contador > tamanho_sequencia)
            {
                tamanho_sequencia = contador;
                tipo_do_pix = PIX[i];
            }
        }

        else
        {
            contador = 1;
        }
    }
    maior_e_tipo[0] = tamanho_sequencia;
    maior_e_tipo[1] = tipo_do_pix;
}


int main(void)
{   
    /* A palavra tipo, usada aqui no programa, é em relação ao tipo do pix
     ou seja, toda vez que aparecer 'tipo' é o tipo do pix, 5, 7 ou 10*/

    int qtde_pix, 
        pix_5, pix_7, pix_10,
        maior_e_tipo[2];

    scanf("%d", &qtde_pix);
    
    int PIX[10000]; //PIX é o vetor com os valores dos PIX's
    pix_recebidos(PIX, qtde_pix);

    pix_5 = qtde_de_cada_tipo(PIX, qtde_pix, 5);
    pix_7 = qtde_de_cada_tipo(PIX, qtde_pix, 7);
    pix_10 = qtde_de_cada_tipo(PIX, qtde_pix, 10);

    /* Acima optei por criar uma variável para guardar a quantidade do tipo
     de cada pix, ao invéz de chamar a função no escopo do printf.
     Isso porque, como o nome da função é muito grande, ficaria muito extenso
     e horrível de ler.*/

    maior_sequencia_e_tipo(PIX, qtde_pix, maior_e_tipo);

    printf("James vendeu %d saladas de 5 reais, %d de 7 reais e %d de 10 reais\n", pix_5, pix_7, pix_10);
    printf("James vendeu %d saladas de %d reais consecutivamente\n", maior_e_tipo[0], maior_e_tipo[1]);
    return 0;
}