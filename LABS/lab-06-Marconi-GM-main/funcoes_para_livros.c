#include "livros.h"


livro *adicionar_livro(livro *ultimo_inserido, char posicao[])
{
    /*  Adiciona livros em qualquer posição necessária, seja no ínicio da lista,
        final ou no meio.
        
        A função recebe o ultimo livro inserido pois, exceto nos casos em que
        se especifíca que deseja-se inserir no início ou no fim, sempre se insere
        na frente do ultimo livro inserido.
        Além disso, também recebe a posição de inserção do livro, sendo elas:
        
        padrao --> insere-se o novo livro na frente do ultimo livro inserido
        inicio --> insere-se no início da lista, na frente da cabeça de lista
        final --> insere-se no final da lista, na frente do último elemento da
                  lista
        Após isso feito, retorna o endereço do novo livro, que agora que já foi 
        inserido na lista, se tornou o ultimo inserido.


        Parâmetros:
        
        ultimo_inserido --> ponteiro, guarda as informações sobre o ultimo livro
                           inserido na lista. Quando a lista está vazia, o ulti
                           mo inserido é a cabeça da lista.

        posicao --> posição onde se deseja realizar a inserção
    */
    int tamanho = 0;
    livro *livro_adicionado;

    // livro que será adicionado
    livro_adicionado = malloc(sizeof(livro));
    livro_adicionado->nome = malloc(MAX * sizeof(char));

    fgets(livro_adicionado->nome, MAX, stdin);
    tamanho = strlen(livro_adicionado->nome);

    // fgets recebe '\n' na ultima posição da string, então trocamos '\n' por '\0'
    livro_adicionado->nome[tamanho - 1] = '\0';

    // inserção no inicio da lista
    if(strcmp(posicao, "inicio") == 0)
    {
        // ultimo_inserido->primeiro sempre guarda o primeiro elemnto da lista
        // ou seja, a cabeça da lista (que nunca será removida).
        livro_adicionado->ant = ultimo_inserido->primeiro;
        livro_adicionado->prox = ultimo_inserido->primeiro->prox;
 
        livro_adicionado->primeiro = ultimo_inserido->primeiro;

        // ultimo_inserido->ultimo sempre guarda o ultimo elemento da lista
        livro_adicionado->ultimo = ultimo_inserido->ultimo;
        
        // atualiza as informações do livro que, por enquanto é o ultimo inserido
        // mas logo após a inserção de livro_adicionado deixará de ser
        ultimo_inserido->primeiro->prox->ant = livro_adicionado;
        ultimo_inserido->primeiro->prox = livro_adicionado;
        
    }

    // as inserções a seguir seguem a mesma lógica da inserção no inicio, com as
    // devidas alterações, por isso pouparei comentários repetitivos

    // inserção no final da lista
    else if(ultimo_inserido->prox == NULL || strcmp(posicao, "final") == 0)
    {

        ultimo_inserido->ultimo->prox = livro_adicionado;
        
        livro_adicionado->ant = ultimo_inserido->ultimo;
        livro_adicionado->prox = NULL;

        livro_adicionado->primeiro = ultimo_inserido->primeiro;
        livro_adicionado->ultimo = livro_adicionado;

        ultimo_inserido->ultimo = livro_adicionado;

    }

    // inserção no meio da lista
    else
    {
        livro_adicionado->ant = ultimo_inserido;
        livro_adicionado->prox = ultimo_inserido->prox;

        livro_adicionado->primeiro = ultimo_inserido->primeiro;
        livro_adicionado->ultimo = ultimo_inserido->ultimo;

        ultimo_inserido->prox->ant = livro_adicionado;
        ultimo_inserido->prox = livro_adicionado;
    }

    return livro_adicionado;
}


void verifica_posicao_e_remove(livro *livro_descartado)
{
    /*  Remove o livro e realiza as conexões entre os nós que o cercavam dependendo
        de qual era sua posição da lista.
        
        Parâmetros:
        
        livro_descartado --> ponteiro, guarda o endereço do livro que será removido
    */

   // se o livro removido estiver na ultima posição da lista
    if(livro_descartado->prox == NULL)
    {
        livro_descartado->ant->prox = NULL;
        livro_descartado->ant->ultimo = livro_descartado->ant;
    }

    // caso contrário esta no meio, pois no inicio temos a cabeça de lista que 
    // nunca será removida.
    else
    {
        livro_descartado->prox->ant = livro_descartado->ant;
        livro_descartado->ant->prox = livro_descartado->prox;
    }

    free(livro_descartado->nome);
    free(livro_descartado);
}


livro *remove_ultimo_inserido(livro *ultimo_inserido, char posicao[])
{
    /*  Remove o livro nos casos especias em que ele foi o último inserido.
        A função recebe o ultimo livro inserido e a posição na qual ele estava.
        A função tem três retornos e sempre retorna o novo 'ultimo_inserido' pois
        é na frente do ultimo livro inserido que se realiza a inserção do pŕoximo.
        Os retornos são:
        
        quando posição == "padrao": neste caso a função retorna o elemento
                                    anterior na lista, pois o próximo elemento
                                    será adicionado na frente desse elemento anterior
        
        posição == "inicio": neste caso a função retorna a cabeça de lista, pois
                             o próximo livro será inserido na frente da cabeça de lista
        
        posição == "final": neste caso a funçaõ retorna o penutimo elemento da lista
                            pois o pŕoximo será inserido na sua frente
                            
        Parâmetros:
        
        ultimo_inserido --> ponteiro, no caso do ultimo inserido e que sera removido
        posicao --> posicao na qual o ultimo livro foi inserido
*/
    livro *cabeca_da_lista = NULL,
          *penultimo_inserido = NULL,
          *final_da_lista = NULL;

    cabeca_da_lista = ultimo_inserido->primeiro;


    if(strcmp(posicao, "padrao") == 0)
    {
        penultimo_inserido = ultimo_inserido->ant;
        ultimo_inserido->ant->prox = ultimo_inserido->prox;

        // Se o ultimo_inserido era o ultimo elemento da lista, então não existe
        // ultimo_inserido->prox, por isso a verificação é necessária
        if(ultimo_inserido->prox != NULL)
        {
            ultimo_inserido->prox->ant = ultimo_inserido->ant;
        }

        // Já se o ultimo inserido era o ultimo, então precisamos atualizar o 
        // ultimo inserido do livro anterior, já que esse será removido.
        if(ultimo_inserido->prox == NULL)
        {
            ultimo_inserido->ant->ultimo = ultimo_inserido->ant;
        }

        free(ultimo_inserido->nome);
        free(ultimo_inserido);

        return penultimo_inserido;
    }

    else if(strcmp(posicao, "inicio") == 0)
    {
        ultimo_inserido->prox->ant = ultimo_inserido->primeiro;
        ultimo_inserido->ant->prox = ultimo_inserido->prox;

        free(ultimo_inserido->nome);
        free(ultimo_inserido);

        return cabeca_da_lista;
    }

    else if(strcmp(posicao, "final") == 0)
    {
        final_da_lista = ultimo_inserido->ant;
        final_da_lista->ultimo = ultimo_inserido->ant;
        ultimo_inserido->ant->prox = NULL;

        free(ultimo_inserido->nome);
        free(ultimo_inserido);

        return final_da_lista;
    }

    // retorna nulo quando algo dá errado.
    return NULL;
}


livro *remover_livro(livro *ultimo_inserido, char posicao[])
{
    /*  Remove os livros, e a depender da sua posição na lista, e da situação,
        chama a função correta para realizar a remoção.
        Após a remoção retorna-se quem é o último inserido, pois as inserções
        futuras dependerão da posição do ultimo_inserido.
        
        Parâmetros:
        
        ultimo_inserido --> ponteiro, no caso do ultimo inserido e que sera removido
        posicao --> posicao na qual o ultimo livro foi inserido    
    */
    int tamanho = 0,
        livro_encontrado = 0;

    livro *livro = NULL;
    char nome_livro_removido[MAX];

    fgets(nome_livro_removido , MAX, stdin);
    tamanho = strlen(nome_livro_removido);

    // fgets recebe '\n' na ultima posição da string, então trocamos '\n' por '\0'
    nome_livro_removido[tamanho - 1] = '\0';

    if(strcmp(ultimo_inserido->nome, "CABECA DA LISTA") == 0)
    {
        printf("A LISTA ESTA VAZIA\n");
    }

    // se o ultimo inserido é o livro a ser removido
    else if(strcmp(ultimo_inserido->nome, nome_livro_removido) == 0)
    {
        if(strcmp(posicao, "padrao") == 0)
        {
            ultimo_inserido = remove_ultimo_inserido(ultimo_inserido, "padrao");
        }

        else if(strcmp(posicao, "inicio") == 0)
        {
            ultimo_inserido = remove_ultimo_inserido(ultimo_inserido, "inicio");
        }

        else if(strcmp(posicao, "final") == 0)
        {
            ultimo_inserido = remove_ultimo_inserido(ultimo_inserido, "final");
        }
    }

    // caso contrário...
    else
    {
        // for para procurar, pelo nome, o livro que queremos remover
        // ultimo_inserido->primeiro é a cabeça da lista 
        for(livro = ultimo_inserido->primeiro; livro_encontrado != 1; livro = livro->prox)
        {
            if(strcmp(livro->nome, nome_livro_removido) == 0)
            {
                livro_encontrado = 1;
                verifica_posicao_e_remove(livro);
                
                return ultimo_inserido;
            }
        }
    }

    // sempre retorna o ultimo inserido
    return ultimo_inserido;
}


void imprimir_livros(livro *ultimo_inserido)
{
    /* Realiza a impressão da lista de livros
    
    Parâmetros:
    
    ultimo_inserido --> ponteiro, guarda as informações do ultimo livro inserido*/
    livro *livros = NULL;

    if(strcmp(ultimo_inserido->nome, "CABECA DA LISTA") == 0)
    {
        printf("Lista VAZIA\n");
    }
    
    else
    {
        // ultimo_inserido->primeiro é a cabeça da lista
        // ulitmo_inserido->primeiro->prox é de fato o primeiro livro da lista
        for(livros = ultimo_inserido->primeiro->prox; livros != NULL; livros = livros->prox)
        {
            // condição para, no último livro, não printar a vírgula e o espaço
            if(livros->prox != NULL)
            {
                printf("%s, ", livros->nome);
            }

            else
            {
                printf("%s\n", livros->nome);
            }
        }
    }
}


livro *cria_cabeca_de_lista(livro *cabeca)
{
    /* Cria a cabeça da lista para facilitar a inserção e remoção dos livros */
    strcpy(cabeca->nome, "CABECA DA LISTA");
    cabeca->ant = NULL;
    cabeca->prox = NULL;
    cabeca->primeiro = cabeca;
    cabeca->ultimo = cabeca;

    return cabeca;
}


livro *libera_lista(livro *ultimo_livro)
{
    /* Libera a memória alocada para a manutenção da lista */
    livro *livro_aux = NULL,
          *anterior = NULL;


    for(livro_aux = ultimo_livro; livro_aux->ant != NULL; livro_aux = anterior)
    {
        anterior = livro_aux->ant;

        free(livro_aux->nome);
        free(livro_aux);
    }

    return livro_aux;
}
