#include "johncc.h"

int tem_parenteses(char *linha)
{
    /* verifica se há parenteses na linha, lida do arquivo
        
        Para isso, a função percorre a linha toda e caso encontre um parenteses
        interrompe a procura e retorna 1, caso não encontre retorna 0
        
        Parâmetros:
        
        *linha --> array de caracteres, a linha lida do arquivo
    */
    int temParenteses = 0;
    for(int i = 0; (linha[i] != '\0') && (temParenteses == 0); i++)
    {
        if(linha[i] == '(')
        {
            temParenteses = 1;
        }
    }

    return temParenteses;
}


int comeca_com_letra(char *linha)
{
    /*  Verifica se a linha, lida do arquivo, começa com letra

        Para isso, a função primeiro verifica se não é uma linha vazia, nesse
        caso o sscanf retorna -1, e logo, a linha não começa com letra.
        Caso a linha não seja vazia, verifica-se se o primeiro caracter
        da primeira palavra, ou expressão, da linha é uma letra.

        Em casos positivos, retorna-se 1, e 0 caso contrário

        Parâmetros:

        linha --> array de caracter, lido do arquivo
    */
    char primeira_palavra[MAX];
    int comecaComLetra = 0;
    int ascii;
    int N;

    N = sscanf(linha, "%s", primeira_palavra);

    if(N == -1)
    {
        comecaComLetra = 0;
    }

    else
    {
        ascii = (int)primeira_palavra[0];

        if((65 <= ascii && ascii <= 90) || (97 <= ascii && ascii <= 122))
        {
            comecaComLetra = 1;
        }
    }
    return comecaComLetra;
}


int eh_declaracao(char *linha)
{
    /*  Verifica se a linha, lida do arquivo, é uma declaração de variável

        Para isso verifica-se a primeira palavra da linha e a compara com char,
        double ou int.

        Retorna 1 caso a houver uma declaração, e 0 caso contrário

        Parâmetros:

        linha --> array de caracter, lido do arquivo    
    */
    char palavra[MAX];
    int ehDeclaracao = 0;

    sscanf(linha, "%s", palavra);

    if(strcmp(palavra, "char") == 0)
    {
        ehDeclaracao = 1;
    }

    else if(strcmp(palavra, "double") == 0)
    {
        ehDeclaracao = 1;
    }

    else if(strcmp(palavra, "int") == 0)
    {
        ehDeclaracao = 1;
    }

    return ehDeclaracao;
}


variavel *cria_variavel(char *linha)
{
    /* Cria uma nova variável
    
        Retorna uma nova variável

        Parâmetros:
        
        linha --> array de caracter, lido do arquivo
    */
    char tipo[10];
    char simbolo[MAX];

    // variável criada apenas para melhorar a leitura do código
    int tamanho = 0;

    variavel *nova_variavel = NULL;
    nova_variavel = malloc(sizeof(variavel));
    

    sscanf(linha, "%s %s", tipo, simbolo);

    // tira o ; do nome da variável
    tamanho = strlen(simbolo);
    simbolo[tamanho - 1] = '\0'; 
    
    strcpy(nova_variavel->tipo, tipo);
    strcpy(nova_variavel->simbolo, simbolo);

    return nova_variavel;
}


int busca_na_arvore(arvore *arv, variavel *var, int linha)
{
    /*  Verifica se uma variável foi declarada, e logo, se está na árvore

        A função retorna um inteiro. 1 para quando a variável foi definida
        e 0 quando ela não foi definida.

        Primeiro, verifica-se se o simbolo da variável e o simobolo do nó da 
        árvore atual são iguais.
        Se sim, atualiza a variavel foi_definida para 1 e atribui o tipo da
        váriavel, que está armazenada na árvore, para a 
        variável auxiliar (var) para facilitar as próximas verificações (tipos
        da variável e se a expressão é válida)

        Caso os simbolos não sejam iguais, verifica se o simbolo procurado é 
        menor ou maior na ordem lexicográfica em relação ao simbolo do nó atual.
        Se for maior na ordem lexi. então procura-se o síbomolo na sub arvore
        direita, recursivamente.
        Se for menor na ordem lexi. procura-se o símbolo na sub árvore esquerda,
        recursivamente.
    
        Parâmetros:

        *arv --> do tipo arvore, arvore na qual se deseja buscar a variável

        *var --> do tipo variável, variável da qual se deseja saber se está ou
                 não na árvore. Variável Auxiliar.

        linha --> int, representa o número da linha em que a execução estava
                  quando se desejou verificar se a variável foi declarada
    */
    int foi_definido = 0;

    if(arv != NULL)
    {
        if(strcmp(arv->var->simbolo, var->simbolo) == 0)
        {
            strcpy(var->tipo, arv->var->tipo);
            foi_definido = 1;
        }

        else
        {
            if(strcmp(var->simbolo, arv->var->simbolo) < 0)
            {
                foi_definido = busca_na_arvore(arv->esq, var, linha);
            }

            else
            {
                foi_definido = busca_na_arvore(arv->dir, var, linha);
            }
        }

    }


    return foi_definido;
}


int verifica_os_tipos(variavel *op2, variavel *op3, char operador, int linha)
{
    /* Compara os tipos do segundo operando e do terceiro operando 
        
        Retorna 1 se os tipos são iguais, 0 caso contrário

        Parâmetros:
        
        *op2 --> variável, armazena o segundo operando
        *op3 --> variável, armazena o terceiro opernado
        operador --> char, o operador da operação entre os operandos
        linha --> int, o número da linha em que se verifica os tipos
                  das variáveis
    */
    int tipos_iguais = 0;

    if(strcmp(op2->tipo, op3->tipo) == 0)
    {
        tipos_iguais = 1;
    }

    else
    {
        tipos_iguais = 0;
        printf("Linha %d: tipos incompatíveis: %s (%s) %c %s (%s).\n", linha, op2->simbolo, op2->tipo, operador, op3->simbolo, op3->tipo);
    }

    return tipos_iguais;
}


int verifica_resultado(variavel *op1, variavel *op2, int linha)
{
    /*  Verifica se o tipo da variavel op1 é o tipo esperado pela operação entre
        as variáveis op2 e op3

        Como os tipos de op2 e op3 são iguais (pois já foi verificado e, se 
        a execução chegou até aqui é porque são iguais) então apenas compara-se
        o op1 com op2, já que o resultado é o mesmo que comparar op1 e op3

        Retorna 1 caso o resultado seja válido, 0 caso contrário
        
        Parâmetro:
        
        *op1 --> variável, armazena o primeiro operando
        *op2 --> variável, armazena o segundo operando
        linha--> int, o número da linha em que se verifica se o resultado é válido
    */
    int resultado_valido = 1;

    if(strcmp(op1->tipo, op2->tipo) != 0)
    {
        resultado_valido = 0;
        printf("Linha %d: tipos incompatíveis: o símbolo %s espera %s, obteve %s.\n", linha, op1->simbolo, op1->tipo, op2->tipo);
    }

    return resultado_valido;
}


int verifica_declaracao(arvore *arv, variavel *op1, variavel *op2, variavel *op3,
                        int numero_da_linha)
{
    /*  Verifica se as variáveis foram declaradas

        Para isso a função faz uso de três variáveis auxiliares.
        Até esse momento da execução, as variáveis auxiliares, op1, op2 e op3
        apenas possuem o símbolo da variável que se deseja verificar se foi de-
        clarada.
        Então, para cada variável, chama-se a função busca na árvore onde ocorrerá
        a busca do símbolo na árvore.
        Caso o a variável esteja na árvore, ou seja, ela foi declarada, dentro
        da função busca_na_arvore() será atribuido o tipo da variável (que está
        na árvore) para a variável auxiliar.
        Dessa maneira, só se realiza a busca uma vez para cada variável, já que 
        op1, op2, e op3 se tornam uma cópia da variável verdadeira e logo para 
        as próximas verificações (de tipos) não será necessário realizar novamente
        a busca

        Parâmetros:

        *arv --> do tipo arvore, arvore onde se deseja verificar se as variaveis
                 foram declaradas
        
        *op1, *op2, *op2 --> variáveis auxiliares

        numero_da_linha  --> int, representa o número da linha em que, no momento
                             da execução, se deseja verificar se as variáveis
                             foram declaradas
    */
    int simbolos_definidos;

    int operando1,
        operando2,
        operando3;
        
    // verifica se o simbolo1 esta na arvore, ou seja, se ele foi declarado
    operando1 = busca_na_arvore(arv, op1, numero_da_linha);

    // se ele foi declarado
    if(operando1)
    {
        // entao verifica-se se o simbolo2 esta na arvore
        operando2 = busca_na_arvore(arv, op2, numero_da_linha);
 
        // se ele foi declarado
        if(operando2)
        {
            // faz o mesmo para o operando3
            operando3 = busca_na_arvore(arv, op3, numero_da_linha);

            // se ele não foi declarado, então operando3 recebe 0, e logo 
            // !operando3 é True
            if(!operando3)
            {
                printf("Linha %d: o símbolo %s não foi definido.\n", numero_da_linha, op3->simbolo);
            }
        }

        else
        {
            printf("Linha %d: o símbolo %s não foi definido.\n", numero_da_linha, op2->simbolo);
        }
    }

    else
    {
        printf("Linha %d: o símbolo %s não foi definido.\n", numero_da_linha, op1->simbolo);
    }

    // se todos os simbolos estao definidos, ou seja: True && True && True
    simbolos_definidos = operando1 && operando2 && operando3;

    return simbolos_definidos;
}


void verifica_expressao(char *linha, arvore *arv, int numero_da_linha,
                        int *ha_erros)
{
    /* Verifica se uma expressão do tipo: OP1 = OP2 Operador OP3 é válida
    
        Para isso a a função lê a linha e atribui à variavis auxiliares 
        (o uso delas está explicado abaixo) os simbolos lidos
        
        Após isso, verifica se a as variáveis foram declaradas,
        se sim, verifica se os tipos são compatíveis,
        se sim verifica se o resultado é valido
        
        Caso um desses três critérios falhem, a função atualiza *ha_erros para 1
        
        Parâmetros: 
        
        *linha --> linha lida do arquivo
        *arv --> do tipo arvore, arv em que se estão armazenadas as variáveis
        numero_da_linha --> int, representa o número da linha no momento em que
                            a execução do programa decidiu verificar a expressão
        *ha_erros --> int *, variavel a fim de verificar se há algum erro durante
                             a execução do programa
    */


    /* Optei pro criar essas variáveis auxiliares.
        Elas ajudarão da seguinte forma: 
        
        > ao ler os símbolos da expressão os guardaremos nas variaveis auxiliares
        > op->simbolo = simbolo lido
        > então verifica-se se esse simbolo foi declarado e está na árvore
        > se sim, além de confirmar que ele foi declarado
        > também será atribuído a essa variavel auxiliar o tipo da variável encontrada
        > variavel_auxiliar->tipo = variavel_verdadeira->tipo
        > op->tipo = variavel_verdadeira->tipo (outra forma de ler)
        > dessa forma op1, op2, op3 funcionarão como copias das verdadeiras variáveis
        > que estão na árvore
        > dessa forma só precisa-se buscar pela variável uma única vez, isso pois
        > para verificar se os tipos são compatíveis e se os resultados são válidos
        > basta verificar usando as cópias das variáveis
        
        Fiz isso pois, cada nó da árvore não é uma variável, ele apenas CONTÉM 
        uma variável, logo essa maneira é uma alternativa pra eu não ter que 
        retornar a árvore toda.

        foi apenas o primeiro insight que tive, não sei se foi o melhor, mas funciona.
        se essa maneira prejudicou muito a leitura, por favor deixa um comentário 
        dizendo e uma critica construtiva :D
    */
    variavel *op1,
             *op2,
             *op3;

    op1 = malloc(sizeof(variavel));
    op2 = malloc(sizeof(variavel));
    op3 = malloc(sizeof(variavel));
    
    char operador,
         igual;

    // inteiros que representarão True (1) ou False (0)
    int simbolos_definidos,
        tipos_iguais,
        resultado_valido;


    // LÊ-SE UMA EXPRESSAÕ DO TIPO " OP1 igual OP2 operador OP3 "
    //                               OP1   =   OP2    +     OP3
    sscanf(linha, "%s %c %s %c %s", op1->simbolo, &igual, op2->simbolo, &operador, op3->simbolo);


    // caso não a linha não seja return 0; então faz-se a análise da expressão
    if(strcmp(op1->simbolo, "return") != 0)
    {
        // retira o ; do simbolo do op3
        op3->simbolo[strlen(op3->simbolo) - 1] = '\0';

        simbolos_definidos = verifica_declaracao(arv, op1, op2, op3, numero_da_linha);

        // se todos os simbolos estão definidos
        if(simbolos_definidos)
        {

            // entao verifica-se se os tipos são compatíveis
            tipos_iguais = verifica_os_tipos(op2, op3, operador, numero_da_linha);

            if(tipos_iguais)
            {

                // se os tipos são compatíveis, verifica-se se o resultado é valido
                resultado_valido = verifica_resultado(op1, op2, numero_da_linha);


                // se o resultado não é valido, então há erros
                if(!resultado_valido && (*ha_erros) == 0)
                {
                    *ha_erros = 1;
                }
            }

            // se os tipos não são compatíveis então há erros
            else if((*ha_erros) == 0)
            {
                *ha_erros = 1;
            }
        }

        // se algum dos símbolos não está definido, então há erros
        else if((*ha_erros) == 0)
        {
            *ha_erros = 1;
        }
    }

    free(op1);
    free(op2);
    free(op3);
}