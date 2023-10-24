#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *searchA();
void *searchB();
void *searchC();

int A[] = {1,2,3,9,11,15,16};
int B[] = {2,3,5,8,9,22};
int C[] = {4,6,9,11};
int i =0,j=0,k=0;
int main(void) {

  // short on = 1;
  // while(on){
  //   if(A[i]<B[j]){
  //     i++;
  //     printf("a");
  //   }
  //   else if(B[j]<C[k]){
  //     j++;
  //     printf("b");

  // }
  //   else if(C[k]<A[i]){
  //     k++;
  //     printf("c");

  //   }
  //   else{
  //     on=0;
  //     break;
  //   }
  // }
  // printf("Wspolna liczba znajduje się w tablicy\nA pod indeksem %d\nB pod indeksem %d\nC pod indeksem %d\n",i,j,k);


  pthread_t threadA;
  pthread_t threadB;
  pthread_t threadC;
  pthread_create(&threadA, NULL, searchA, NULL);
  pthread_create(&threadB, NULL, searchB, NULL);
  pthread_create(&threadC, NULL, searchC, NULL);

  pthread_join(threadA, NULL);
  pthread_join(threadB, NULL);
  pthread_join(threadC, NULL);

  printf("Wspolna liczba znajduje sie w tablicy\nA pod indeksem %d\nB pod indeksem %d\nC pod indeksem %d\n",i,j,k);

  return 0;
}

void *searchA(){
  while(A[i]<=B[j]||B[j]<=C[k]||C[k]<=A[i]){
    if(A[i]<B[j]){
      i++;
    }
    else if(A[i]==B[j]&& B[j]==C[k]) break;
  }

  pthread_exit(NULL);
}

void *searchB(){
  while(A[i]<=B[j]||B[j]<=C[k]||C[k]<=A[i]){

    if(B[j]<C[k]){
      j++;
    }
    else if(A[i]==B[j]&& B[j]==C[k]) break;

  }
  pthread_exit(NULL);
}

void *searchC(){

  while(A[i]<=B[j]||B[j]<=C[k]||C[k]<=A[i]){
    if(C[k]<A[i]){
      k++;
    }
    else if(A[i]==B[j] && B[j]==C[k]) break;
  }
  pthread_exit(NULL);
}
