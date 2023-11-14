#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

typedef struct log_info
{                    // estrutura que armazena quantidades de operações (comparações e trocas)
    int comparacoes; // e tempo de processamento
    int trocas;
    double tempo;
} log_info;

void insertion_sort(int *, int, log_info *);
void insertion_sortBB(int *, int, log_info *);
void shellsort(int *, int, log_info *);
int busca_binaria(int *, int, int, int, log_info *);

int main(void)
{
    log_info logRandom, logCresc, logDecresc;     // armazena contadores de comparações e trocas, além do tempo
    clock_t t;
    
    srand(time(NULL));

    //faz o processo em array de 100, 1000 e 10000 elementos
    for(int j = 1; j <= MAX; j = j * 10)
    {
        //aloca as arrays
        int *arrayrandom = (int *)malloc(sizeof(int) * (MAX*j));
        int *arraycrescente = (int *)malloc(sizeof(int) * (MAX*j));
        int *arraydecrescente = (int *)malloc(sizeof(int) * (MAX*j));

        // Gera os 3 tipos de array
        for (int i = 0; i < MAX * j; i++)
            arrayrandom[i] = rand() % (MAX * j); // gera números aleatórios para o array
        for (int i = 0; i < MAX * j; i++)
            arraycrescente[i] = i; // gera números em ordem crescente
        for (int i = 0; i < MAX * j; i++)
            arraydecrescente[i] = (MAX * j) - i; // gera números em ordem decrescente  
    
        //ordena array aleatorio
        t = clock();
        insertion_sort(arrayrandom, MAX * j, &logRandom);
        t = clock() - t;
        logRandom.tempo = ((double)t) / CLOCKS_PER_SEC;

        //ordena array em ordem cresc
        t = clock();
        insertion_sort(arraycrescente, MAX * j, &logCresc);
        t = clock() - t;
        logCresc.tempo = ((double)t) / CLOCKS_PER_SEC; 

        //ordena array em ordem decresecente
        t = clock();
        insertion_sort(arraydecrescente, MAX * j, &logDecresc);
        t = clock() - t;
        logDecresc.tempo = ((double)t) / CLOCKS_PER_SEC; 

        //tabela com os resultados
        printf("\n------------------------------------------------------------------");
        printf("\n%d Elementos:\n\nARRAY\t\t\tTROCAS\t\tCOMPARACOES\tTEMPO\n", MAX * j);
        printf("\nAleatorio");
        printf("\t\t%d", logRandom.trocas);
        printf("\t\t%d", logRandom.comparacoes);
        printf("\t\t%fs", logRandom.tempo);
        printf("\n");
        printf("\nCrescente");
        printf("\t\t%d", logCresc.trocas);
        printf("\t\t%d", logCresc.comparacoes);
        printf("\t\t%fs", logCresc.tempo);
        printf("\n");
        printf("\nDecrescente");
        printf("\t\t%d", logDecresc.trocas);
        printf("\t\t%d", logDecresc.comparacoes);
        printf("\t\t%fs", logDecresc.tempo);
        printf("\n");

        //libera a memoria alocada
        free(arrayrandom);
        free(arraycrescente);
        free(arraydecrescente);
    }

    return 0;
}

// Função de Inserção Direta com Busca Linear
void insertion_sort(int *array, int array_size, log_info *log)
{
    log->trocas = 0;
    log->comparacoes = 0;
    for (int i = 1; i < array_size; i++)
    {                         // do segundo ao último
        int chave = array[i]; // chave a inserir no subarray ordenado
        int j = i - 1;        // último elemento do subarray ordenado
        log->comparacoes++;
        while (j >= 0 && array[j] > chave)
        { // busca linear da direita para a esquerda no subarray ordenado
            log->comparacoes++;
            array[j + 1] = array[j];
            j = j - 1;
            log->trocas++;
        }
        if (j + 1 != i)
        {
            array[j + 1] = chave;
            log->trocas++;
        }
    }
}

// *****************************************************
//  TODO: Implementação dos seus algoritmos (a seguir)
// *****************************************************
//funçao pra realizar a bucsa binaria e retornar a posição que deve ser inserida na array(se retornar -1 deve ser inserida na posição 0)
int buscaBinaria(int primeiro, int ultimo, int *array, int chave, int *comp)
{
    //acha o meio da array
    int meio = (primeiro + ultimo) / 2;

    //se nao tiver nenhum elemento igual a chave na array
    if (primeiro == ultimo && chave != array[meio])
    {
        *comp = *comp + 1;
        if(chave > array[meio])
            return meio + 1;
        else
            return meio - 1;
    }

    //se tiver um elemento igual a chave na array
    if(array[meio] == chave)
    {
        *comp = *comp + 1;
        return meio + 1;
    }

    //se o elemento do meio for maior que a chave
    if(array[meio] > chave)
    {
        *comp = *comp + 1;
        return buscaBinaria(primeiro, meio - 1, array, chave, comp);
    }
    //se o elemento do meio for menor que a chave
    else
    {
        *comp = *comp + 1;
        return buscaBinaria(meio + 1, ultimo, array, chave, comp);
    }
}

// Função de Inserção com Busca Binária (incompleta)
// Provavelmente você terá que implementar a Função
// auxiliar de busca binária (não esqueça de registrar eventuais
// comparações que ela fizer)
void insertion_sortBB(int *array, int array_size, log_info *log)
{
    log->trocas = 0;
    log->comparacoes = 0;
}

// Função de Shellsort  (incompleta)
void shellsort(int *array, int array_size, log_info *log)
{
    log->comparacoes = 0;
    log->trocas = 0;
}