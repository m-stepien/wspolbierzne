#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

double sumArr[MAX];

typedef struct s_threadData {
  int num;
  int threadId;
} s_threadData;

void *countSum(void *arg);

int main(void) {
  const char *FILE_NAME = "file.txt";

  FILE *file = fopen(FILE_NAME, "r");

  if (file == NULL) {
      return 1;
  }

  int num;
  int numberArr[MAX]; 
  int numCount = 0; 

  while (fscanf(file, "%d", &num) == 1) {
      if (numCount < MAX) {
          numberArr[numCount] = num;
          numCount++;
      } else {
          printf("Przekroczono MAX (%d).\n", MAX);
          break;
      }
  }
  fclose(file);
  pthread_t thread[numCount];
  s_threadData data[numCount];
  for(int i = 0; i<numCount; i++){
    data[i].num = numberArr[i];
    data[i].threadId = i;
    pthread_create(&thread[i], NULL, countSum, &data[i]);
  }

  for(int i = 0; i<numCount; i++){
    pthread_join(thread[i], NULL);
  }
  
  for (int i = 0; i < numCount; i++) {
      printf("%lf,\t", sumArr[i]);
  }
}
void *countSum(void *arg){
  s_threadData *data = (s_threadData *)arg;
  int sum = 0;
  for(int i = 1; i < data->num; i++){
    sum+=i;
  }
  sumArr[data->threadId] = (double) sum;
  pthread_exit(NULL);
}
