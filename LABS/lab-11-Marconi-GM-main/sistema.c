#include "sistema.h"


int char_para_binario(char caracter)
{
    /*  Dado um caracter, a função calcula seu binário e o devolve
    
        Para isso a função segue o seguinte algoritmo:
        > enquanto a divisão inteira, do ascii do caracter por 2, for maior que zero
        > multiplica, o resto da divisão de ascii por 2 (ascci mod 2), por 10 elevado à
        > i-ésima potência, onde i é um natural, correspondente à mesma potencia que
        > eleva o 2 ao escrever-se ascii em binário.
        > exemplo:
        > 5 em binário é 101 = 1*10² + 0 * 10¹ + 1 * 10⁰

        Parâmetros:

        caracter --> char, correspodente ao caracter que quer-se escrever em
                     binário
    */
    int ascii = 0;
    int binario = 0;

    ascii = (int)caracter;
    for(int i = 0; ascii / 2 > 0; i++)
    {
        binario += ( (ascii % 2) * (pow(10, i)) ); 
        ascii /= 2;
        
        if(ascii == 1)
        {
            binario += (1 * pow(10, i+1));
        }
    }

    return binario;
}


int hash(char *familia, int i)
{
    /*  Dado um nome de uma família, calcula um número correspondente ao seu nome
        e o devolve

        Para isso a função usa em sua conta o número binário de cada caractér
        que compoe o nóme da família.
        Por isso, faz-se necessário o indice i, um inteiro que corresponde à
        posição no nome da familia, ou seja, o caracter que está na posição 
        familia[i].

        Para calcular o hash a função faz uso da função disponibilizada no slide
        das aulas

        Parâmetros:

        *familia --> string, correspondente ao nome da família
        i --> inteiro, corresponde à posição que se quer acessar na string familia
    */
    int hash_final;
    if(familia[i] == '\0')
    {
        return 0;
    }

    else
    {
        hash_final = ((char_para_binario(familia[i]) % MAX) * 256 + hash(familia, i+1)) % MAX;
    }

    return hash_final;
}


int hash_duplo(char *familia)
{
    /*  Calcula um segundo hash, para os casos em que um hash anteriormente calculado
        já está em uso, e o retorna.

        ~~~comentário pessoal: rapaziada nao consegui pensar em uma função
        criativa para esse hash, ou seja, uma que espalhasse bem, mas essa
        funcionou, então vou deixar ela assim mesmo, o uso do 157 foi arbitrário
        achei que ele daria uma boa ajuda e deu certo

        Seu cálculo se dá da seguinte maneira:
        > para cada caractér que compoe o nome da familia, calcula-se seu 
        > binario e então calcula-se binario % 157 o soma em uma variável

        Parêmtros:

        *familia --> string, correspondente ao nome da familia
    */
    int novo_hash = 0;
    for(int i = 0; familia[i] != '\0'; i++)
    {
        novo_hash += (char_para_binario(familia[i]) % 157);
    }

    return novo_hash;
}


void inclui_familia(sistema *banco_de_dados, char familia[], int doces)
{
    /*  Inclui a familia no sistema

        Para isso, a função calcula um hash, caso a posição desse número hash
        já esteja em uso na tabela, ela calcula um segundo número hash, no qual
        a posição está livre.

        Feito isso, ela atualiza os dados dessa posição na tabela, incluindo a 
        familia no sistema
    
        Parâmetros:

        *banco_de_dados --> do tipo sistema, é a tabela de hashing
        *familia --> string, correspondente ao nome da família
        doces --> int, número de doces que a familia possui
    */
    int chave;
    int novo_hash;

    chave = hash(familia, 0);

    if(banco_de_dados[chave].endereco_vazio == 1)
    {
        banco_de_dados[chave].qtde_doces = doces;
        banco_de_dados[chave].endereco_vazio = 0;
        banco_de_dados[chave].familia_saiu = 0;
        strcpy(banco_de_dados[chave].familia, familia);
    }

    else
    {
        novo_hash = hash_duplo(familia);
        for(int i = 1; banco_de_dados[novo_hash].endereco_vazio == 0; i++)
        {
            novo_hash = (chave + (i * novo_hash)) % MAX;
        }

        banco_de_dados[novo_hash].qtde_doces = doces;
        banco_de_dados[novo_hash].endereco_vazio = 0;
        banco_de_dados[novo_hash].familia_saiu = 0;
        strcpy(banco_de_dados[novo_hash].familia, familia);

    }

}


int encontra_familia(sistema *banco_de_dados, char familia[])
{
    /*  Percorre a tabela de hashing, procurando pela familia e devolve a chave,
    o ńúmero do hash, a posição, dessa família na tabela
    
        Para isso a função verifica se a família está na posição de seu primeiro
        hash, caso não esteja ela faz o procura em hash's possíveis,
        
        Após encontrar devolve a posição
        
        Parâmetros:
        
        *banco_de_Dados --> do tipo sistema, é a tabela de hashing
        *familia --> string, nome da familia da qual se deseja saber a posição
                     na tabela
    */
    int chave;
    int novo_hash;

    chave = hash(familia, 0);
    if(strcmp(banco_de_dados[chave].familia, familia) == 0)
    {
        return chave;
    }

   else
    {
        novo_hash = hash_duplo(familia);
        for(int i = 1; strcmp(banco_de_dados[novo_hash].familia, familia) != 0; i++)
        {
            novo_hash = (chave + (i * novo_hash)) % MAX;
        }

        if(banco_de_dados[novo_hash].familia_saiu == 0)
        {
            return novo_hash;
        }
    }

    // Se nao encontrar a familia, então retorna dummy -99
    return -99;
}


void remove_familia(sistema *banco_de_dados, char familia[])
{
    /* Remove a familia do sistema, quando ela sai de sua casa
    
        Para isso, a função altera o campo da struct sistema, o qual
        possui a informação se a família está em casa ou não.
        O altera para 1 quando ela não está em casa, e 0
        para quando ela está em casa
        
        Parâmetros:

        *banco_de_Dados --> do tipo sistema, é a tabela de hashing
        *familia --> string, nome da familia da qual se deseja saber a posição
                     na tabela
        
        */
    int chave;

    chave = encontra_familia(banco_de_dados, familia);

    banco_de_dados[chave].familia_saiu = 1;
    printf("A familia %s saiu com %d doce(s) sobrando.\n", familia, banco_de_dados[chave].qtde_doces);
}


void atualiza_qtde_doces(sistema *banco_de_dados, char familia[], int doces)
{
    /* Atualiza a quantidade de doces de uma familia

        Para isso a função, encontra a posição da familia na tabela,
        e atualiza a quantidade
    
        Parâmetros:
        
        *banco_de_Dados --> do tipo sistema, é a tabela de hashing
        *familia --> string, nome da familia da qual se deseja saber a posição
                     na tabela
        doces --> inteiro, corresponde ao número de doces que será somado ao
                  número atual de doces da família, perceba que esse número
                  pode ser negativo, no caso em que a família doa doces à crianças
                  então ao somar-se um negativo, se subtrai da quantidade total
    */
    int chave;

    chave = encontra_familia(banco_de_dados, familia);
    banco_de_dados[chave].qtde_doces += doces;

    // só para garantir que não haverá quantidades negativas de doces
    if(banco_de_dados[chave].qtde_doces < 0)
    {
        banco_de_dados[chave].qtde_doces = 0;
    }

    if(doces >= 0)
    {
        printf("A familia %s agora possui %d doces.\n", familia, banco_de_dados[chave].qtde_doces);
    }

    else if(banco_de_dados[chave].qtde_doces == 0)
    {
        printf("A familia %s ficou sem doces.\n", familia);
    }


}

void trickortreat(sistema *banco_de_dados, char nome[], char sobrenome[], int casas)
{
    /* Trick or treat */
    char familia[FAMILIA];
    char nota[7];

    int doces_totais = 0;
    int chave = 0;

    // para cada casa
    for(int i = 0; i < casas; i++)
    {
        // lê-se o nome da família e sua nota
        scanf("%s %s", familia, nota);

        // encontra a familia na tabela de hash
        chave = encontra_familia(banco_de_dados, familia);

        // se a nota for boa
        if(strcmp(nota, "Boa") == 0)
        {
            // e a familia possuir quantidade suficiente de doces
            if(banco_de_dados[chave].qtde_doces >= 3)
            {
                doces_totais += 3;
                atualiza_qtde_doces(banco_de_dados, familia, -3);
            }

            // caso não possua 
            else if(banco_de_dados[chave].qtde_doces > 0)
            {
                doces_totais += banco_de_dados[chave].qtde_doces;
                banco_de_dados[chave].qtde_doces = 0;
                printf("A familia %s ficou sem doces.\n", banco_de_dados[chave].familia);
            }
        }

        // se a nota for média
        else if(strcmp(nota, "Media") == 0)
        {
            // e a família possuir quantidade suficiente de doces
            if(banco_de_dados[chave].qtde_doces >= 2)
            {
                doces_totais += 2;
                atualiza_qtde_doces(banco_de_dados, familia, -2);
            }

            // caso ñão possua
            else if(banco_de_dados[chave].qtde_doces > 0)
            {
                doces_totais += banco_de_dados[chave].qtde_doces;
                banco_de_dados[chave].qtde_doces = 0;
                printf("A familia %s ficou sem doces.\n", banco_de_dados[chave].familia);
            }
        }

        // se a nota for ruim
        else if(strcmp(nota, "Ruim") == 0)
        {
            // e a família possuir quantidade suficiente de doces
            if(banco_de_dados[chave].qtde_doces >= 1)
            {
                doces_totais += 1;
                atualiza_qtde_doces(banco_de_dados, familia, -1);
            }

            // caso não possua
            else if(banco_de_dados[chave].qtde_doces > 0)
            {
                doces_totais += banco_de_dados[chave].qtde_doces;
                banco_de_dados[chave].qtde_doces = 0;
                printf("A familia %s ficou sem doces.\n", banco_de_dados[chave].familia);
            }
        }
    }

    // se ao final a criança tiver ganho algum doce
    if(doces_totais > 0)
    {
        printf("%s %s recebeu %d doce(s) das familias.\n", nome, sobrenome, doces_totais);
    }

    // caso contrário
    else
    {
        printf("%s %s recebeu 10 doces da prefeitura.\n", nome, sobrenome);
    }
}


sistema *cria_sistema()
{
    /* Cria um sistema e inicializa seus atributos */
    sistema *novo_sistema;
    novo_sistema = malloc(MAX_FAMILIAS * sizeof(sistema));

    for(int i = 0; i < MAX_FAMILIAS; i++)
    {
        novo_sistema[i].familia_saiu = 0;
        novo_sistema[i].qtde_doces = 0;
        novo_sistema[i].endereco_vazio = 1;
        strcpy(novo_sistema[i].familia, "NULL");
    }

    return novo_sistema;
}