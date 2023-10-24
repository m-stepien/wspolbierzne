#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100
#define THREAD_NUM 5


typedef struct s_range {
  int start;
  int end;
  int threadId;
} s_range;

typedef struct s_divisible{
int by3;
int by5;
int by7;
} s_divisible;

s_divisible divisible[THREAD_NUM];
int array[ARRAY_SIZE];



void printArray(int arr[]);
void *findDivNum(void* range);

int main(void) {
  srand(time(NULL));
  int sumDiv3=0;
  int sumDiv5=0;
  int sumDiv7=0;

  for (int i = 0; i < ARRAY_SIZE; i++) {
    array[i] = (rand() % 1000) + 1;
  }
  printArray(&array);

  s_range rangeForThread[THREAD_NUM];
  pthread_t thread[THREAD_NUM];
  for(int i = 0; i<THREAD_NUM; i++){
    rangeForThread[i].start = i * (ARRAY_SIZE/THREAD_NUM);
    rangeForThread[i].end = i*(ARRAY_SIZE/THREAD_NUM)+ARRAY_SIZE/THREAD_NUM;
    rangeForThread[i].threadId = i;
    if(i == THREAD_NUM-1){
      rangeForThread[i].end += ARRAY_SIZE%THREAD_NUM;
    }
    pthread_create(&thread[i], NULL, findDivNum, &rangeForThread[i]);
  }

  for(int i = 0; i<THREAD_NUM; i++){
    pthread_join(thread[i], NULL);
  }

  for(int i = 0; i<THREAD_NUM; i++){
    sumDiv3 += divisible[i].by3;
    sumDiv5 += divisible[i].by5;
    sumDiv7 += divisible[i].by7;
  }
  printf("W tablicy znajduje się\n%d - liczb podzielnych przez 3\n%d - liczb podzielnych przez 5\n%d - liczb podzielnych przez 7", sumDiv3, sumDiv5, sumDiv7);
  return 0;
}

void printArray(int arr[]) {
  for (int i = 0; i < ARRAY_SIZE; i++) {
    printf("%d,\t", arr[i]);
  }
  printf("\n_________________________________________\n");
}

void *findDivNum(void *range) {
  s_range *p = (s_range *)range;
  divisible[p->threadId].by3 = 0;
  divisible[p->threadId].by5 = 0;
  divisible[p->threadId].by7 = 0;
  
  for (int i = p->start+1; i < p->end; i++) {
    if(array[i]%3==0)divisible[p->threadId].by3+=1;
    if(array[i]%5==0)divisible[p->threadId].by5+=1;
    if(array[i]%7==0)divisible[p->threadId].by7+=1;
  }
  pthread_exit(NULL);
}
