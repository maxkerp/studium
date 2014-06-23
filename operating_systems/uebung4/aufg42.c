#include <stdio.h> //exit(0) included
#include <stdlib.h>  // printf
#include <sys/types.h> // for process id pid_t / pid
#include <unistd.h>  // system api fork, write, read
#include <pthread.h> // for POSIX threads

//global vars
pthread_t mainChild1, mainChild2;

typedef struct childs_struct {
  int time1;
  int time2;
} child_struct_parms;

int getRandom (int min,int max) {
  return(rand()%(max-min)+min);
}

void randomThread (void *parms) {
  printf("random request startet\n");
  printf("random request finished\n");
}

void handle_childs (void *parms) {
  int *responseTime;
  responseTime = (int *) parms;
  int myRandomNumber = getRandom(0, *responseTime);
  printf("a child thread. response time %d seconds\n", *responseTime);
  for (int i = 0; i < *responseTime; i++) {
    if (i == myRandomNumber) {
      pthread_t random;
      pthread_create(&random, NULL, (void *) &randomThread, NULL);
      pthread_join(random, NULL);
    }
    sleep(1);
  }
  printf("exiting child thread...\n");
}

void create_childs (void *parms) {
  printf("main thread\n");
  child_struct_parms *data;
  data = (child_struct_parms *) parms;

  pthread_create(&mainChild1, NULL, (void *) &handle_childs, (void *) &data->time1);
  pthread_create(&mainChild2, NULL, (void *) &handle_childs, (void *) &data->time2);

  pthread_join(mainChild1, NULL);
  pthread_join(mainChild2, NULL);
  printf("exit main thread\n");
}

int main () {
  pthread_t main;
  child_struct_parms data;
  data.time1 = 3;
  data.time2 = 5;

  pthread_create(&main, NULL, (void *) &create_childs, (void *) &data);
  //clean exit

  pthread_join(main, NULL);
  exit(0);
}

