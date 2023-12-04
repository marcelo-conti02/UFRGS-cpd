#include <stdio.h>
#include <time.h>
#include <stdbool.h>

struct log_info
{
    int comparacoes;
    int trocas;
};

struct array_info
{
    int *array;
    int size;
};

void merge(int *, int, int *, int, int *, struct log_info *);
void two_way_merge(struct array_info *, int, int *, struct log_info *);
void multi_way_merge(struct array_info *, int, int *, struct log_info *);

int main(void)
{
    struct log_info log;
    struct array_info arrays[3];
    int array1[] = {1, 2, 4, 6, 7, 8, 15, 22};
    int array2[] = {1, 2, 3, 4, 5, 6, 7, 8, 25, 27, 35, 44};
    int array3[20];
    int array4[40];
    double tempo;
    clock_t t;

    merge(array1, 8, array2, 12, array3, &log);

    arrays[0].array = array1;
    arrays[1].array = array2;
    arrays[2].array = array3;

    arrays[0].size = 8;
    arrays[1].size = 12;
    arrays[2].size = 20;

    t = clock();
    two_way_merge(arrays, 3, array4, &log);
    t = clock() - t;

    printf("Resultado two-way merge: ");
    for (int i = 0; i < 40; i++)
        printf("%d ", array4[i]);
    printf("\n");

    tempo = ((double)t) / CLOCKS_PER_SEC; // em segundos
    printf("Tempo de processamento: %f segundos\n", tempo);

    t = clock();
    multi_way_merge(arrays, 3, array4, &log);
    t = clock() - t;

    printf("Resultado multi-way merge: ");
    for (int i = 0; i < 40; i++)
        printf("%d ", array4[i]);
    printf("\n");

    tempo = ((double)t) / CLOCKS_PER_SEC; // em segundos
    printf("Tempo de processamento: %f segundos\n", tempo);

    return 0;
}

// ################################################
// Algoritmos de intercalação
// ################################################
void merge(int *array1, int size1, int *array2, int size2, int *array_final, struct log_info *loginfo)
{
    int i = 0, j = 0, pos = 0;

    loginfo->trocas = 0;
    loginfo->comparacoes = 0;

    bool elementos = true;

    while (i < size1 && j < size2)
    {
        loginfo->comparacoes++;
        loginfo->trocas++;
        if (array1[i] <= array2[j])
            array_final[pos++] = array1[i++];
        else
            array_final[pos++] = array2[j++];
    }

    if (j < size2 && i >= size1) // array 1 terminou
        for (int e = j; e < size2; e++)
        {
            array_final[pos++] = array2[e];
            loginfo->trocas++;
        }

    if (i < size1 && j >= size2) // array 2 terminou
        for (int e = i; e < size2; e++)
        {
            array_final[pos++] = array1[e];
            loginfo->trocas++;
        }
}

// Two_way_merge: recebe uma lista de arrays e intercala-os 2 a 2.
// Lembre-se de que o algoritmo não é local (resultado sai em novo array).
// havendo mais de 2, um array temporário é usado para intercalar os arrays.
// retorna um array com o resultado da intercalação.
void two_way_merge(struct array_info *arrays, int qtd_arrays, int *array_final, struct log_info *log)
{
    int size, n;

    for (int i = 0; i < qtd_arrays - 1; i++)
        n = n + arrays[i].size + arrays[i+1].size;                                      //define tamanho do array auxiliar(soma dos tamanhos das arrays)
    int aux[n];

    merge(arrays[0].array, arrays[0].size, arrays[1].array, arrays[1].size, aux, log);  //primeiro merge
    size = arrays[0].size + arrays[1].size;                                             //elementos na array auxiliar

    for (int i = 2; i < qtd_arrays; i++)                                                //faz os merges a partir do 3 array
    {
        merge(aux, size, arrays[i].array, arrays[i].size, array_final, log);
        size = size + arrays[i].size;                                                   //atualiza a quantidade de elementos no aux

        if(i+1 != qtd_arrays)                                                           //se nao for o ultimo merge
        {
            for (int j = 0; j < size; j++)                                              //passa os valores de array final para o aux
                array_final[j] = aux[j];
        }
    }
}

// multi_way_merge: recebe uma lista de arrays e intercala-os usando estrutura similar a heap-min
// Lembre-se de que o algoritmo não é local (resultado sai em novo array).
void multi_way_merge(struct array_info *arrays, int qtd_arrays, int *array_final, struct log_info *log)
{
    int pos = 0;

    for (int i = 0; i < qtd_arrays; i++)
    {
        for (int j = 0; j < arrays[i].size; j++)
        {
            array_final[pos++] = arrays[i].array[j];
        }
    }

    // TODO: implementar direito, pois só concatena
}