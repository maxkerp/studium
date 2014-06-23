#include <stdio.h> //exit(0) included
#include <stdlib.h>  // printf
#include <sys/types.h> // for process id pid_t / pid
#include <unistd.h>  // system api fork, write, read
#include <time.h> // time header

//global vars
pid_t *pids; // array für pids

void createChildren(int count) {
  //allocate enough memory for upcoming pids
  pids = calloc(count, sizeof(pid_t));

  int procNum;

  for(procNum = 0; procNum < count; procNum++) {
    pids[procNum] = fork();
    //break because of loop in loop
    if (pids[procNum] == 0) {
      break;
    }
    else if (pids[procNum] < 0) {
      printf("Fork Error\n");
    }
  }
  //functionality for created children
  if (pids[procNum] == 0) {
    int totalTime = (getpid()) % 10;
    sleep(totalTime);
    //return current child pid
    printf("PID: %d\n", getpid());
    // runtime
    printf("Total: %ds\n", totalTime);
    // timestamp when finished
    printf("Timestamp: %d\n", (int)time(NULL));
    printf("-----------------\n");
  }
}

int main () {
  //create forks with integer argument
  int childrenCount = 3;
  createChildren(childrenCount);
  //wait for all pids
  int returnStatus;
  for (int i = 0; i < childrenCount; i++) {
    waitpid(pids[i], &returnStatus, 0);
  }
  if (returnStatus == 0) {
    printf("\nchild processes finished without error\n");
  }
  if (returnStatus == 1) {
    printf("child process error\n");
  }
  //free allocated memory
  free(pids);
  //clean exit
  exit(0);
  //with command "echo $" you get the result of main in a shell
}

