#include <stdio.h> //exit(0) included
#include <stdlib.h>  // printf
#include <sys/types.h> // for process id pid_t / pid
#include <unistd.h>  // system api fork, write, read
#include <pthread.h> // for POSIX threads

typedef struct char_print_parms_type {  //
  int counter;  //counter n1 || n2
  int threadNum;
  char character; //charater to display later
} char_print_parms;

void char_print(void *parameters) {
  char_print_parms *data;
  data = (char_print_parms *) parameters;
  for (int i = 0; i < data->counter; i++) {
    printf("Thread #%d: %c\n", data->threadNum, data->character);
  }
  printf("\n");
}

int main () {
  pthread_t thread1, thread2; //pthread placeholder
  char_print_parms data1, data2; //pthread data struct

  //init first struct
  data1.threadNum = 1;
  data1.character = 'a';
  data1.counter = 43;

  //init second struct
  data2.threadNum = 2;
  data2.character = 'b';
  data2.counter = 17;

  //create thread1+2, give them a function and a pointer to their struct
  pthread_create(&thread1, NULL, (void *) &char_print, (void *) &data1);
  pthread_create(&thread2, NULL, (void *) &char_print, (void *) &data2);

  //wait for both threads to finisih
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  //clean exit
  exit(0);
}

