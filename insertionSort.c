#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX1 100
#define MAX2 1000 // tamanho dos arrays
#define MAX3 10000

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
    int *array = (int *)malloc((sizeof(int) * MAX1) * 3);
    int *arrayrandom = (int *)malloc(sizeof(int) * MAX1);
    int *arraycrescente = (int *)malloc(sizeof(int) * MAX1);
    int *arraydecrescente = (int *)malloc(sizeof(int) * MAX1); // array dinâmico que armazena os números
    log_info logRandom, logCresc, logDecresc;                                              // armazena contadores de comparações e trocas, além do tempo
    clock_t t;
    
    srand(time(NULL));

    // Gera os 3 tipos de array
    for (int i = 0; i < MAX1; i++)
        arrayrandom[i] = rand() % MAX1; // gera números aleatórios para o array
    for (int i = 0; i < MAX1; i++)
        arraycrescente[i] = i; // gera números em ordem crescente
    for (int i = 0; i < MAX1; i++)
        arraydecrescente[i] = MAX1 - i; // gera números em ordem decrescente
    
    //ordena array aleatorio
    t = clock();
    insertion_sort(arrayrandom, MAX1, &logRandom);
    t = clock() - t;
    logRandom.tempo = ((double)t) / CLOCKS_PER_SEC;

    //ordena array em ordem cresc
    t = clock();
    insertion_sort(arraycrescente, MAX1, &logCresc);
    t = clock() - t;
    logCresc.tempo = ((double)t) / CLOCKS_PER_SEC; 

    //ordena array em ordem decresecente
    t = clock();
    insertion_sort(arraydecrescente, MAX1, &logDecresc);
    t = clock() - t;
    logDecresc.tempo = ((double)t) / CLOCKS_PER_SEC; 

    //tabela com os resultados
    printf("\n------------------------------------------------------------------");
    printf("\n100 Elementos:");
    printf("\n");
    printf("\nARRAY");
    printf("\t\tTROCAS");
    printf("\t\tCOMPARAÇÕES");
    printf("\tTEMPO");
    printf("\n");
    printf("\nAleatorio");
    printf("\t%d", logRandom.trocas);
    printf("\t\t%d", logRandom.comparacoes);
    printf("\t\t%fs", logRandom.tempo);
    printf("\n");
    printf("\nCrescente");
    printf("\t%d", logCresc.trocas);
    printf("\t\t%d", logCresc.comparacoes);
    printf("\t\t%fs", logCresc.tempo);
    printf("\n");
    printf("\nDecrescente");
    printf("\t%d", logDecresc.trocas);
    printf("\t\t%d", logDecresc.comparacoes);
    printf("\t\t%fs", logDecresc.tempo);
    printf("\n");
    printf("\n------------------------------------------------------------------");


    // TODO: mostrar informações de execução de todos os algoritmos nos diferentes tipos de array

    free(arrayrandom);
    free(arraycrescente);
    free(arraydecrescente);

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