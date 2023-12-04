#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <cstdlib>

#define MAX 100

struct log_info
{
    int comparacoes;
    int trocas;
};

void mergesort(int *, int, int, struct log_info *);
void merge(int array[], int i, int m, int f, struct log_info *loginfo);

int main(void)
{
    struct log_info logCresc;
    struct log_info logDecresc;
    double tempo;
    clock_t t;
    //  faz o processo em array de 100, 1000 e 10000 elementos
    for (int j = 1; j <= MAX; j = j * 10)
    {
        logCresc.comparacoes = 0;
        logDecresc.comparacoes = 0;
        logCresc.trocas = 0;
        logDecresc.trocas = 0;
        // aloca as arrays
        int *arraycrescente = (int *)malloc(sizeof(int) * (MAX * j));
        int *arraydecrescente = (int *)malloc(sizeof(int) * (MAX * j));

        // Gera os 2 tipos de array para o mergesort
        for (int i = 0; i < MAX * j; i++)
            arraycrescente[i] = i; // gera números em ordem crescente
        for (int i = 0; i < MAX * j; i++)
            arraydecrescente[i] = (MAX * j) - i; // gera números em ordem decrescente

        // ordena array em ordem cresc
        t = clock();
        mergesort(arraycrescente, 0, (MAX * j) - 1, &logCresc);
        t = clock() - t;
        tempo = ((double)t) / CLOCKS_PER_SEC;

        printf("\nMergesort em array com %d elementos crescente: \n", MAX * j);
        printf("Comparacoes: %d\n", logCresc.comparacoes);
        printf("Trocas: %d\n", logCresc.trocas);
        printf("Tempo: %fsegundos\n", tempo);

        // ordena array em ordem decresecente
        t = clock();
        mergesort(arraydecrescente, 0, (MAX * j) - 1, &logDecresc);
        t = clock() - t;
        tempo = ((double)t) / CLOCKS_PER_SEC;

        printf("\nMergesort em array com %d elementos decrescente: \n", MAX * j);
        printf("Comparacoes: %d\n", logDecresc.comparacoes);
        printf("Trocas: %d\n", logDecresc.trocas);
        printf("Tempo: %fsegundos\n", tempo);
    }
    return 0;
}

// ################################################
// Algoritmos de intercalação
// ################################################

void mergesort(int *array, int i, int f, struct log_info *loginfo)
{
    if (i < f)
    {
        int m = (i + f) / 2;
        mergesort(array, i, m, loginfo);
        mergesort(array, m + 1, f, loginfo);
        merge(array, i, m, f, loginfo);
    }
}

void merge(int arr[], int left, int middle, int right, struct log_info *loginfo)
{
    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    int *leftArray = (int *)malloc(n1 * sizeof(int));
    int *rightArray = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        leftArray[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        rightArray[j] = arr[middle + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        loginfo->comparacoes++;
        loginfo->trocas++;
        if (leftArray[i] <= rightArray[j])
        {
            arr[k] = leftArray[i];
            i++;
        }
        else
        {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        loginfo->trocas++;
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        loginfo->trocas++;
        arr[k] = rightArray[j];
        j++;
        k++;
    }

    free(leftArray);
    free(rightArray);
}