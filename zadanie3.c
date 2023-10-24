#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100
#define THREAD_NUM 5

int array[ARRAY_SIZE];
int sumInThread[THREAD_NUM];

typedef struct s_range {
  int start;
  int end;
  int threadId;
} s_range;

void printArray(int arr[]);
void *sumArrayEleements(void* range);

int main(void) {
  srand(time(NULL));
  int sumOfAll = 0;

  for (int i = 0; i < ARRAY_SIZE; i++) {
    array[i] = (rand() % 1000) + 1;
  }
  printArray(&array);

  s_range rangeForThread[THREAD_NUM];
  pthread_t thread[THREAD_NUM];
  for(int i = 0; i<THREAD_NUM; i++){
    rangeForThread[i].threadId = i;
    rangeForThread[i].start = i * (ARRAY_SIZE/THREAD_NUM);
    rangeForThread[i].end = i*(ARRAY_SIZE/THREAD_NUM)+ARRAY_SIZE/THREAD_NUM;
    if(i == THREAD_NUM-1){
      rangeForThread[i].end += ARRAY_SIZE%THREAD_NUM;
    }
    pthread_create(&thread[i], NULL, sumArrayEleements,        &rangeForThread[i]);
  }

  for(int i = 0; i<THREAD_NUM; i++){
    pthread_join(thread[i], NULL);
  }

  for(int i =0; i<THREAD_NUM; i++){
    sumOfAll += sumInThread[i];
  }
  
  printf("Suma liczb w tablicy wynosi: %d", sumOfAll);
  return 0;
}

void printArray(int arr[]) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    printf("%d,\t", arr[i]);
  }
  printf("\n_________________________________________\n");
}

void *sumArrayEleements(void *range) {
  s_range *p = (s_range *)range;
  sumInThread[p->threadId] = 0;
  for (int i = p->start; i < p->end; i++) {
    sumInThread[p->threadId] += array[i];
  }
  pthread_exit(NULL);
}
