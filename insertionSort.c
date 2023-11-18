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
int buscaBinaria(int primeiro, int ultimo, int *array, int chave, int *comp);

int main(void)
{
    log_info logRandomIS, logCrescIS, logDecrescIS, logRandomISBB, logCrescISBB, logDecrescISBB, logRandomShell, logCrescShell, logDecrescShell;
    clock_t t;

    srand(time(NULL));

    // faz o processo em array de 100, 1000 e 10000 elementos
    for (int j = 1; j <= MAX; j = j * 10)
    {
        // aloca as arrays
        int *arrayrandom = (int *)malloc(sizeof(int) * (MAX * j));
        int *arraycrescente = (int *)malloc(sizeof(int) * (MAX * j));
        int *arraydecrescente = (int *)malloc(sizeof(int) * (MAX * j));

        // Gera os 3 tipos de array para inserção com busca simples
        for (int i = 0; i < MAX * j; i++)
            arrayrandom[i] = rand() % (MAX * j); // gera números aleatórios para o array
        for (int i = 0; i < MAX * j; i++)
            arraycrescente[i] = i; // gera números em ordem crescente
        for (int i = 0; i < MAX * j; i++)
            arraydecrescente[i] = (MAX * j) - i; // gera números em ordem decrescente

        // ordena array aleatorio
        t = clock();
        insertion_sort(arrayrandom, MAX * j, &logRandomIS);
        t = clock() - t;
        logRandomIS.tempo = ((double)t) / CLOCKS_PER_SEC;

        // ordena array em ordem cresc
        t = clock();
        insertion_sort(arraycrescente, MAX * j, &logCrescIS);
        t = clock() - t;
        logCrescIS.tempo = ((double)t) / CLOCKS_PER_SEC;

        // ordena array em ordem decresecente
        t = clock();
        insertion_sort(arraydecrescente, MAX * j, &logDecrescIS);
        t = clock() - t;
        logDecrescIS.tempo = ((double)t) / CLOCKS_PER_SEC;

        // Gera os 3 tipos de array PARA INSERÇÃO COM BUSCA BINARIA
        for (int i = 0; i < MAX * j; i++)
            arrayrandom[i] = rand() % (MAX * j); // gera números aleatórios para o array
        for (int i = 0; i < MAX * j; i++)
            arraycrescente[i] = i; // gera números em ordem crescente
        for (int i = 0; i < MAX * j; i++)
            arraydecrescente[i] = (MAX * j) - i; // gera números em ordem decrescente

        // ordena array aleatorio
        t = clock();
        insertion_sortBB(arrayrandom, MAX * j, &logRandomISBB);
        t = clock() - t;
        logRandomISBB.tempo = ((double)t) / CLOCKS_PER_SEC;

        // ordena array em ordem cresc
        t = clock();
        insertion_sortBB(arraycrescente, MAX * j, &logCrescISBB);
        t = clock() - t;
        logCrescISBB.tempo = ((double)t) / CLOCKS_PER_SEC;

        // ordena array em ordem decresecente
        t = clock();
        insertion_sortBB(arraydecrescente, MAX * j, &logDecrescISBB);
        t = clock() - t;
        logDecrescISBB.tempo = ((double)t) / CLOCKS_PER_SEC;

        // Gera os 3 tipos de array PARA SHELLSORT
        for (int i = 0; i < MAX * j; i++)
            arrayrandom[i] = rand() % (MAX * j); // gera números aleatórios para o array
        for (int i = 0; i < MAX * j; i++)
            arraycrescente[i] = i; // gera números em ordem crescente
        for (int i = 0; i < MAX * j; i++)
            arraydecrescente[i] = (MAX * j) - i; // gera números em ordem decrescente

        // ordena array aleatorio
        t = clock();
        shellsort(arrayrandom, MAX * j, &logRandomShell);
        t = clock() - t;
        logRandomShell.tempo = ((double)t) / CLOCKS_PER_SEC;

        // ordena array em ordem cresc
        t = clock();
        shellsort(arraycrescente, MAX * j, &logCrescShell);
        t = clock() - t;
        logCrescShell.tempo = ((double)t) / CLOCKS_PER_SEC;

        // ordena array em ordem decresecente
        t = clock();
        shellsort(arraydecrescente, MAX * j, &logDecrescShell);
        t = clock() - t;
        logDecrescShell.tempo = ((double)t) / CLOCKS_PER_SEC;

        // tabela com os resultados
        printf("\n------------------------------------------------------------------");
        printf("\n%d Elementos:\n", MAX * j);
        printf("\nAleatorio insertion_sort:");
        printf("   %d trocas", logRandomIS.trocas);
        printf("   %d comparacoes", logRandomIS.comparacoes);
        printf("   %fs", logRandomIS.tempo);
        printf("\nAleatorio insertion_sortBB:");
        printf("   %d trocas", logRandomISBB.trocas);
        printf("   %d comparacoes", logRandomISBB.comparacoes);
        printf("   %fs", logRandomISBB.tempo);
        printf("\nAleatorio shellsort:");
        printf("   %d trocas", logRandomShell.trocas);
        printf("   %d comparacoes", logRandomShell.comparacoes);
        printf("   %fs", logRandomShell.tempo);
        printf("\n");
        printf("\nCrescente insertion_sort:");
        printf("   %d trocas", logCrescIS.trocas);
        printf("   %d comparacoes", logCrescIS.comparacoes);
        printf("   %fs", logCrescIS.tempo);
        printf("\nCrescente insertion_sortBB:");
        printf("   %d trocas", logCrescISBB.trocas);
        printf("   %d comparacoes", logCrescISBB.comparacoes);
        printf("   %fs", logCrescISBB.tempo);
        printf("\nCrescente shellsort:");
        printf("   %d trocas", logCrescShell.trocas);
        printf("   %d comparacoes", logCrescShell.comparacoes);
        printf("   %fs", logCrescShell.tempo);
        printf("\n");
        printf("\nDecrescente insertion_sort:");
        printf("   %d trocas", logDecrescIS.trocas);
        printf("   %d comparacoes", logDecrescIS.comparacoes);
        printf("   %fs", logDecrescIS.tempo);
        printf("\nDecrescente insertion_sortBB:");
        printf("   %d trocas", logDecrescISBB.trocas);
        printf("   %d comparacoes", logDecrescISBB.comparacoes);
        printf("   %fs", logDecrescISBB.tempo);
        printf("\nDecrescente shellsort:");
        printf("   %d trocas", logDecrescShell.trocas);
        printf("   %d comparacoes", logDecrescShell.comparacoes);
        printf("   %fs", logDecrescShell.tempo);
        printf("\n");

        // libera a memoria alocada
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
// funçao pra realizar a bucsa binaria e retornar a posição que deve ser inserida na array
int buscaBinaria(int primeiro, int ultimo, int *array, int chave, int *comp)
{
    while (primeiro <= ultimo)
    {
        int meio = primeiro + (ultimo - primeiro) / 2;

        // se o valor do meio da busca é igual a chave
        if (array[meio] == chave)
        {
            *comp = *comp + 1;
            return meio;
        }
        // procura na metade menor
        if (array[meio] > chave)
        {
            ultimo = meio - 1;
            *comp = *comp + 1;
        }
        // metade maior
        else
        {
            *comp = *comp + 1;
            primeiro = meio + 1;
        }
    }
    // se nao tiver estiver na array
    return primeiro;
}

// Função de Inserção com Busca Binária (incompleta)
// Provavelmente você terá que implementar a Função
// auxiliar de busca binária (não esqueça de registrar eventuais
// comparações que ela fizer)
void insertion_sortBB(int *array, int array_size, log_info *log)
{
    log->trocas = 0;
    log->comparacoes = 0;
    for (int i = 1; i < array_size; i++)
    {                                                            // do segundo ao último
        int chave = array[i];                                    // chave a inserir no subarray ordenado
        int j = i - 1;                                           // último elemento do subarray ordenado
        int compbb = 0;                                          // variavel pra calcular as comparaçoes na busca binaria
        int posicao = buscaBinaria(0, j, array, chave, &compbb); // acha a posição com busca binaria
        log->comparacoes = log->comparacoes + compbb;            // soma as compracoes da busca binaria

        // move os elementos da array ordenada pra direita
        while (j >= posicao)
        {
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

// Função de Shellsort  (incompleta)
void shellsort(int *array, int array_size, log_info *log)
{
    log->comparacoes = 0;
    log->trocas = 0;
    int gap, i, j, chave;

    // define os intervalos
    for (gap = array_size / 2; gap > 0; gap = gap / 2)
    {
        for (i = gap; i < array_size; i += gap) //varredura com o intervalo
        {
            chave = array[i];
            j = i - gap;
            log->comparacoes++;
            while (j >= 0 && array[j] > chave) //faz as comparações
            {
                log->comparacoes++;
                array[j + gap] = array[j];
                j = j - gap;
                log->trocas++;
            }
            if (j + gap != i)
            {
                array[j + gap] = chave;
                log->trocas++;
            }
        }
    }
}