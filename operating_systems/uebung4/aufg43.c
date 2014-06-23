#include <stdio.h> //exit(0) included
#include <stdlib.h>  // printf
#include <pthread.h> // for POSIX threads
#include <unistd.h>

void handleThread () {
  while (1) {
    sleep(5);
    printf("waited 5 seconds\n");
  }
}

int main () {
  int bytes_read;
  size_t nbytes = 100;
  char *my_string;

  pthread_t aThread;
  pthread_create(&aThread, NULL, (void *) &handleThread, NULL);

  printf("to kill child thread press enter\n");

  my_string = (char *) malloc (nbytes);
  bytes_read = getline (&my_string, &nbytes, stdin);

  if (bytes_read == -1) {
    printf("ERROR!\n");
    exit(0);
  }
  else {
    pthread_cancel(aThread);
    printf("child thread canceled\n");
  }

  pthread_join(aThread, NULL);

  //clean exit
  exit(0);
}
