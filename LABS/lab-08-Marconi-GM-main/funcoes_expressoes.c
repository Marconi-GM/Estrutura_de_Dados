#include "funcoes_expressoes.h"


int eh_variavel(char x)
{
    /* Verifica se o caractér x é uma variável
       A função faz a checagem do código ascii do caracter e retorna uma
       resposta, 0 em caso negativo e 1 caso negativo
       
       Parâmetros:
       
       x --> char, o caracter que será avaliado
    */
    int resposta = 0;
    int ascii;
    ascii = (int)x;

    if(97 <= ascii && ascii <= 122)
    {
        resposta = 1;
    }

    return resposta;
}


int eh_inteiro(char x)
{
    /* Verifica se o caractér x é um inteiro
       A função faz a checagem do código ascii do caracter e retorna uma
       resposta, 0 em caso negativo e 1 caso negativo
       
       Parâmetros:
       
       x --> char, o caracter que será avaliado
    */
    int resposta = 0;
    int ascii;
    ascii = (int)x;
    
    if(48 <= ascii && ascii <= 57)
    {
        resposta = 1;
    }

    return resposta;
}


int eh_operador(char x)
{   
    /* Verifica se o caractér x é um operador
       A função faz a checagem do código ascii do caracter e retorna uma
       resposta, 0 em caso negativo e 1 caso negativo
       
       Parâmetros:
       
       x --> char, o caracter que será avaliado
    */
    int resposta = 0;
    char  operadores[8] = {'>', '<', '{', '}', '&', '|', '=', '!'};

    for(int i = 0; i < 8; i++)
    {
        if(operadores[i] == x)
        {
            resposta = 1;
        }
    }

    return resposta;
}

char otimiza(char operador, char op1, char op2)
{
    /*  Otimiza uma expressão entre dois operandos e um operador para T ou F,
        isto é, para T, true, quando a expressão é valida e para F, false, caso
        contrário.
        
        Para isso, verifica-se o tipo de operador e então os operandos.
        Retorna um caracter, F ou T, dependendo do resultado da otimização
        
        Parâmetros:
        
        operador: char, representa o operador binário entre os operandos
        op1: char, representa o operando à esquerda do operador
        op2: char, representa o operando à direita do operador
    */
    char resultado;
    if(operador == '>')
    {
        if(eh_inteiro(op1) && eh_inteiro(op2))
        {
            if((int)op1 > (int)op2)
            {
                resultado = 'T';
            }

            else
            {
                resultado = 'F';
            }
        }

        // temos 0 > (algo), como zero não é maior que nada: F
        else if(op1 == '0')
        {
            resultado = 'F';
        }

        // temos (algo) > 9, como, aqui, nada é maior que 9: F
        else if(op2 == '9')
        {
            resultado = 'F';
        }

        else if(eh_variavel(op1) && eh_variavel(op2))
        {
            if(op1 == op2)
            {
                resultado = 'F';
            }
        }
    }

    else if(operador == '<')
    {
        if(eh_inteiro(op1) && eh_inteiro(op2))
        {
            if((int)op1 < (int)op2)
            {
                resultado = 'T';
            }

            else
            {
                resultado = 'F';
            }
        }

        // análogo da análise feita mais acima, temos 9 < (algo), nada é maior
        // que 9  
        else if(op1 == '9')
        {
            resultado = 'F';
        }

        // análogo à análise feita mais acima
        else if(op2 == '0')
        {
            resultado = 'F';
        }

        else if(eh_variavel(op1) && eh_variavel(op2))
        {
            if(op1 == op2)
            {
                resultado = 'F';
            }
        }
    }

    else if(operador == '{')
    {
        if(eh_inteiro(op1) && eh_inteiro(op2))
        {
            if((int)op1 <= (int)op2)
            {
                resultado = 'T';
            }

            else
            {
                resultado = 'F';
            }
        }

        // temos (variavel) { 9, logo, verdadeiro
        else if(op2 == '9')
        {
            resultado = 'T';
        }

        else if(eh_variavel(op1) && eh_variavel(op2))
        {
            if(op1 == op2)
            {
                resultado = 'T';
            }
        }
    }

    else if(operador == '}')
    {
        if(eh_inteiro(op1) && eh_inteiro(op2))
        {
            if((int)op1 >= (int)op2)
            {
                resultado = 'T';
            }

            else
            {
                resultado = 'F';
            }
        }

        // análogo à análise feita mais acima
        else if(op1 == '9')
        {
            resultado = 'T';
        }

        // tudo é maior ou igual a zero
        else if(op2 == '0')
        {
            resultado = 'T';
        }


        else if(eh_variavel(op1) && eh_variavel(op2))
        {
            if(op1 == op2)
            {
                resultado = 'T';
            }
        }
    }

    else if(operador == '&')
    {
        if(op1 == 'F' || op2 == 'F')
        {
            resultado = 'F';
        }
    }

    else if(operador == '|')
    {
        if(op1 == 'T' || op2 == 'T')
        {
            resultado = 'T';
        }
    }

    else if(operador == '!')
    {
        if(op1 == op2)
        {
            resultado = 'F';
        }

        else
        {
            resultado = 'T';
        }
    }

    else if(operador == '=')
    {
        if(op1 == op2)
        {
            resultado = 'T';
        }

        else
        {
            resultado = 'F';
        }
    }

    return resultado;
}


int eh_otimizavel(char operador, char operando1, char operando2)
{
    /*  Verifica se podemos otimizar a expressão entre os operandos e seu operador
        
        Para isso verifica-se qual o operador da expressão e então verifica-se
        os tipos dos operandos.
        
        retorna o resultado da análise, 1 para quando é possivel otimizar
        e zero caso contrário.
        
        Parâmetros:

        operador: char, representa o operador binário entre os operandos
        operando1: char, representa o operando à esquerda do operador
        operando2: char, representa o operando à direita do operador
    */
    int eh_possivel = 0;

    if(operador == '<' || operador == '>' || operador == '{' || operador == '}')
    {
        if(eh_inteiro(operando1) && eh_inteiro(operando2))
        {
            eh_possivel = 1;
        }

        else if(eh_variavel(operando1) && eh_variavel(operando2))
        {
            if(operando1 == operando2)
            {
                eh_possivel = 1;
            }

            // else apenas para melhor a legibilidade
            else
            {
                eh_possivel = 0;
            }
        }

        else if(operando1 == '9' || operando2 == '9')
        {
            // temos um dos operandos como um nove e o outro é uma variavel
            if(eh_variavel(operando1) || eh_variavel(operando2))
            {
                if(operando1 == '9' && operador == '<')
                {
                    eh_possivel = 1;
                }

                else if(operando1 == '9' && operador == '}')
                {
                    eh_possivel = 1;
                }

                else if(operando2 == '9' && operador == '{')
                {
                    eh_possivel = 1;
                }

                else if(operando2 == '9' && operador == '>')
                {
                    eh_possivel = 1;
                }
                
                else
                {
                    eh_possivel = 0;
                }
            }
            
            else if(operador == '{' || operador == '>' || operador == '<')
            {
                eh_possivel = 1;
            }
        }

        else if(operando1 == '0' || operando2 == '0')
        {
            if(operador == '}' || operador == '<' || operador == '>')
            {
                if((eh_inteiro(operando1) && eh_inteiro(operando2)))
                {
                    eh_possivel = 1;
                }

                else if(operando1 == operando2)
                {
                    eh_possivel = 1;
                }

                else if(operador == '>' && operando1 == '0')
                {
                    eh_possivel = 1;
                }

                else if(operador == '<' && operando2 == '0')
                {
                    eh_possivel = 1;
                }

            }
        }
    }

    else if(operador == '&' || operador == '|')
    {
        if(operador == '|')
        {
            if(operando1 == 'T' || operando2 == 'T')
            {
                eh_possivel = 'T';
            }
        }

        else if(operador == '&')
        {
            if(operando1 == 'F' || operando2 == 'F')
            {
                eh_possivel = 'F';
            }
        }
    }

    else if(operador == '=' || operador == '!')
    {
        if(eh_inteiro(operando1) && eh_inteiro(operando2))
        {
            eh_possivel = 1;
        }

        else if(operando1 == 'T' || operando1 == 'F')
        {
            if(operando2 == 'T' || operando2 == 'F')
            {
                eh_possivel = 1;
            }
        }

        else if(eh_variavel(operando1) && eh_variavel(operando2))
        {
            if(operando1 == operando2)
            {
                eh_possivel = 1;
            }

            else
            {
                eh_possivel = 0;
            }
        }
    }

    return eh_possivel;
}
