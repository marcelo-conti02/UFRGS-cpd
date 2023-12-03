#include<stdio.h>
#include<time.h>

#define SIZE 8                                                                  // tamanho dos arrays

struct log_info{                                                                // estrutura que armazena quantidades de operações (comparações e trocas)
  int comparacoes;                                                              //  durante o processamento de um algoritmo
  int trocas;
};

void selectionsort(int*, int, struct log_info*);
void heapsort(int*, int, struct log_info*);
void buildheap(int*, int, struct log_info*);
void heapify(int*, int, int, struct log_info*);
int filho_e(const int*, int);
int filho_d(const int*, int);
int pai(const int*, int);
int heap_max(int* heap);
int extract_max(int* heap, int elemento, int* heap_size, struct log_info* loginfo);
void insert_heap(int* heap, int *heap_size, int chave);
void buildheapMax(int* array, int array_size, struct log_info* loginfo);
void heapsortMax(int* array, int heap_size, struct log_info* loginfo);

int main(void){
  struct log_info log;                                                          // armazena contadores de comparações e trocas
  double tempo;
  clock_t t;
  int heap_size = SIZE;

  int array1[] = {1,2,3,4,5,6,7,8};
  int array2[] = {9,8,7,6,5,4,3,1};

  printf("Array original 1: ");
  for(int i=0; i<SIZE; i++)
     printf("%d ", array1[i]);
  printf("\n");

  // buildheap

  t = clock();
  buildheap(array2, SIZE, &log);
  t = clock() - t;

  printf("Array transformado em Heap: ");
  for(int i=0; i<SIZE; i++)
     printf("%d ", array1[i]);
  printf("\n");

  printf("Primeiro elemento do heap: ");
  int primeiro = heap_max(array1);
  printf("%d", primeiro);
  printf("\n");


  printf("Heap apos extract_heap: ");
  extract_max(array1, 0, &heap_size, &log);
  for(int i=0; i < heap_size; i++)
     printf("%d ", array1[i]);
  printf("\n");

  printf("Heap apos insert_heap: ");
  insert_heap(array1, &heap_size, 9);
  for(int i=0; i < heap_size; i++)
     printf("%d ", array1[i]);
  printf("\n");

  tempo = ((double)t)/CLOCKS_PER_SEC; // em segundos
  printf("Tempo de processamento: %f segundos\n", tempo);

  // heapsort

  printf("Array original 2: ");
  for(int i=0; i<SIZE; i++)
     printf("%d ", array2[i]);
  printf("\n");

  t = clock();
  heapsortMax(array2, SIZE, &log);
  t = clock() - t;

  printf("Array após heapsort: ");
  for(int i=0; i<SIZE; i++)
     printf("%d ", array2[i]);
  printf("\n");

  tempo = ((double)t)/CLOCKS_PER_SEC; // em segundos
  printf("Tempo de processamento: %f segundos\n", tempo);

  return 0;
}

// ################################################
// Algoritmos de ordenação por Seleção
// ################################################

// Seleção direta
void selectionsort(int* array, int qtd_elementos, struct log_info* loginfo){
   int tmp;
   int menorchave;

   loginfo->trocas = 0;
   loginfo->comparacoes = 0;

   for(int i=0; i<qtd_elementos;i++){
      menorchave = i;
      for(int j=i; j<qtd_elementos+1; j++){
         loginfo->comparacoes++;
         if(array[j] < array[menorchave]){
            menorchave = j;
         }
      }
      if(menorchave != i){
         int tmp = array[i];
         array[i] = array[menorchave];
         array[menorchave] = tmp;
         loginfo->trocas++;
      }
   }
}

// Heapsort
void heapsort(int* array, int heap_size, struct log_info* loginfo){
   int tmp;
   int qtd_elementos = heap_size-1;

   loginfo->trocas = 0;
   loginfo->comparacoes = 0;

   buildheap(array, heap_size, loginfo);

   for(int i = qtd_elementos; i>0; i--){
      loginfo->trocas++;
      tmp = array[i];
      array[i] = array[0];
      array[0] = tmp;
      heap_size--;
      heapify(array, 0, heap_size, loginfo);
   }
}

// Heapsort
void heapsortMax(int* array, int heap_size, struct log_info* loginfo){
   int tmp;
   int qtd_elementos = heap_size-1;

   loginfo->trocas = 0;
   loginfo->comparacoes = 0;

   buildheapMax(array, heap_size, loginfo);

   for(int i = qtd_elementos; i>0; i--){
      loginfo->trocas++;
      tmp = array[i];
      array[i] = array[0];
      array[0] = tmp;
      heap_size--;
      heapify(array, 0, heap_size, loginfo);
   }
}

// usada no heapsort
void buildheap(int* array, int array_size, struct log_info* loginfo){
   int ultimo_pai = (array_size/2)-1;
   for(int i=ultimo_pai; i>=0; i--)
      heapify(array, i, array_size, loginfo);
}

// usada no heapsort
void buildheapMax(int* array, int array_size, struct log_info* loginfo){
   int ultimo_pai = (array_size/2)-1;
   int flag;
   for(int i=0; i<=ultimo_pai; i++)
   {
      int j = i;
      while(j>=0)
      {
         heapify(array, j, array_size, loginfo);
         j--;
      }
   }
}

// heapify: verifica se o elemento na posição passada é um heap e se o não for, transforma-o em um heap
// lembre-se de que a análise é feita de maneira recursiva, sendo realizada somente no lado em que
// um dos filhos for maior do que o pai (se isso ocorrer)
void heapify(int* array, int elemento, int heap_size, struct log_info* loginfo){
    int maior = elemento;
    int tmp;
    int esquerdo = filho_e(array, elemento);
    int direito = filho_d(array, elemento);

    loginfo->comparacoes+=2;
    if(esquerdo < heap_size && array[esquerdo]>array[maior])
       maior = esquerdo;

    if(direito < heap_size && array[direito]>array[maior])
       maior = direito;

    if(maior!=elemento){
      tmp = array[maior];
      array[maior] = array[elemento];
      array[elemento] = tmp;
      loginfo->trocas++;
      heapify(array, maior, heap_size, loginfo);
    }
}

int filho_e(const int* array, int elemento){
   return elemento*2+1;
}

int filho_d(const int* array, int elemento){
   return elemento*2+2;
}

int pai(const int* array, int elemento){
   return (elemento-1)/2;
}

int heap_max(int* heap){   //retorna o primeiro elemento do heap(sem remove-lo do heap)
    return heap[0];
}

int extract_max(int* heap, int elemento, int *heap_size, struct log_info* loginfo){   //retorna e extrai o primeiro elemento do heap, reajustando-o de maneira a garantir que o array continue sendo um heap
    int max;
    max = heap[0];
    heap[0] = heap[*heap_size - 1];
    *heap_size -= 1;
    heapify(heap, elemento, *heap_size, loginfo);
    return max;
}

void insert_heap(int* heap, int *heap_size, int chave){   //insere no heap
    *heap_size += 1;
    int i = *heap_size - 1;
    while(i > 0 && heap[pai(heap, i)] < chave)
    {
        heap[i] = heap[pai(heap, i)];
        i = pai(heap, i);
    }
    heap[i] = chave;
}