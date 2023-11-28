#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

#define N_ALGOs 2                                                               // Qtd de algoritmos a serem testados
#define QTD_ARRAYS 3                                                            // quantidade de arrays a serem processados (1 por tipo)
#define POTENCIAS 5                                                             // potências de 10 a serem testadas como tamanhos de arrays

struct log_info{
  int comparacoes;
  int trocas;
  double tempo;
  int tamanho;
  char sigla[5];
  char tipo;
};

struct algo_info{
  char name[15];
  char acronym[5];
  void (*function)(int*, int, struct log_info*);
};

struct array_info{
  char name[15];
  char type;
  int* contents;
};

void bubblesort(int*, int, struct log_info*);
void quicksort(int*, int, struct log_info*);
void quicksort_aux(int*, int, int, struct log_info*);
int particiona(int*, int, int, struct log_info*);
void swap(int *, int *);

int main(void){
  int info_total = N_ALGOs*3*(POTENCIAS-2);
  struct algo_info algoritmos[N_ALGOs];                                                // array de structs que armazenam as funções dos algoritmos a testar
  struct array_info arrays[3];                                                         // array de informações sobre arrays a serem processados
  struct log_info results[info_total];                                                 // armazena resultados do processamento de um algoritmo em um array
  struct log_info log;                                                                 // armazena contadores de comparações e trocas, além do tempo
  int* tmp_array;
  clock_t t;
  int i, algo, arr, size, potencia, result;

  // inicializa array com informações sobre os algoritmos a serem testados
  strcpy(algoritmos[0].name, "Bubblesort");
  strcpy(algoritmos[0].acronym, "BBST");
  algoritmos[0].function = &bubblesort;

  strcpy(algoritmos[1].name, "Quicksort");
  strcpy(algoritmos[1].acronym, "QQST");
  algoritmos[1].function = &quicksort;

  srand(42);                                                                    // inicializa gerador de números aleatórios
  result = 0;

  // cria e inicializa arrays de diferentes tamanhos
  for(potencia=2;potencia<POTENCIAS;potencia++){
    size = (int)pow(10.0, (float)potencia);

    strcpy(arrays[0].name, "Crescente");
    arrays[0].type = 'C';
    arrays[0].contents = (int*) malloc(sizeof(int)*size);
    strcpy(arrays[1].name, "Decrescente");
    arrays[1].type = 'D';
    arrays[1].contents = (int*) malloc(sizeof(int)*size);
    strcpy(arrays[2].name, "Randômico");
    arrays[2].type = 'R';
    arrays[2].contents = (int*) malloc(sizeof(int)*size);

    for(i=0;i<size;i++){
      arrays[0].contents[i] = i+1;                                                // array decrescente
      arrays[1].contents[i] = size-i;                                             // array decrescente
      arrays[2].contents[i] = rand() % size;                                      // array aleatório
    }

    // testa algoritmos com os arrays
    tmp_array = (int*) malloc(sizeof(int)*size);
    for(arr=0;arr<QTD_ARRAYS;arr++){
      printf("Array %s de tamanho %d gerado: ", arrays[arr].name, size);
      for(i=0;i<size;i++) printf("%d ", arrays[arr].contents[i]);
      printf("\n");

      for(algo=0; algo<N_ALGOs; algo++){
        printf("\nOrdenando array por %s...\n", algoritmos[algo].name);
        memcpy(tmp_array, arrays[arr].contents, sizeof(int)*size);

        t = clock();
        algoritmos[algo].function(tmp_array, size, &results[result]);
        results[result].tempo = ((double)(clock()-t))/CLOCKS_PER_SEC;                         // tempo decorrido (em segundos)

        printf("\nArray ordenado: ");
        for(i=0;i<size;i++) printf("%d ", tmp_array[i]);

        printf("\nQuantidade de trocas: %d", results[result].trocas);
        printf("\nQuantidade de comparações: %d", results[result].comparacoes);
        printf("\nTempo de processamento: %f segundos\n", results[result].tempo);

        strcpy(results[result].sigla, algoritmos[algo].acronym);
        results[result].tipo = arrays[arr].type;
        results[result].tamanho = size;
        result++;
      }
      printf("\n");
    }
    printf("\n");

    free(tmp_array);
    for(arr=0;i<QTD_ARRAYS;arr++) free(arrays[arr].contents);
  }

  printf("Algoritmo - Array -  Tamanho - Comparações -    Trocas   -  Tempo (s)\n");
  for(i=0;i<info_total;i++) printf("%9s - %5c - %8d - %11d - %11d - %10.7f\n", results[i].sigla, results[i].tipo, results[i].tamanho, results[i].comparacoes, results[i].trocas, results[i].tempo);

  return 0;
}

// *****************************************************************************
// Funções de Ordenação

void bubblesort(int* array, int array_size, struct log_info* log){
    int trocas = 0;
    int comparacoes = 0;
    int pos_troca = 0;
    bool troca = true;
    int qtd_elementos = array_size-1;

    while(troca){
        troca = false;
        for(int i=0; i<qtd_elementos;i++){
            comparacoes = comparacoes + 1;
            if(array[i] > array[i+1]){
              swap(&array[i], &array[i+1]);
              troca = true;
              pos_troca = i;
              trocas = trocas + 1;
            }
        }
        qtd_elementos = pos_troca;
    }

    log->trocas = trocas;
    log->comparacoes = comparacoes;
}

void quicksort(int* array, int array_size, struct log_info* log){
  log->trocas = 0;
  log->comparacoes = 0;
  quicksort_aux(array, 0, array_size-1, log);
}

void quicksort_aux(int* array, int i, int f, struct log_info* log){
    int p;
    if(f>i){
		  p = particiona(array, i, f, log);
		  quicksort_aux(array, i, p-1, log);
		  quicksort_aux(array, p+1, f, log);
	}
}

int particiona(int* array, int esq, int dir, struct log_info* log){
  int i=esq+1, j=dir, pivo=esq;
  while(j>i){
    while(array[i]<array[pivo] && i<dir) {
      i++;
      log->comparacoes++;
    }
    while(array[j]>=array[pivo] && j>esq){
      j--;
      log->comparacoes++;
    }

    if(i<j && array[i]>array[j]){
      swap(&array[i], &array[j]);
      log->comparacoes++;
      log->trocas++;
    }
  }

  if(array[j]<array[pivo]){
	  swap(&array[pivo], &array[j]);
    log->comparacoes++;
    log->trocas++;
  }
  return j;
}

void swap(int *n1, int *n2){
	int troca = *n1;
	*n1 = *n2;
	*n2 = troca;
}