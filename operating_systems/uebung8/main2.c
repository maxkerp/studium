/* Task 8-2
 *
 *
 */

#include <stdlib.h>       //exit(0) included
#include <stdio.h>        //printf
#include <sys/types.h>    //for process id pid_t
#include <unistd.h>       //system api fork, write, read
#include <string.h>       //string library

#define PIPE_BUFFER 100

int add2 (int x, int y) {
  return x+y;
}

int main (int argc, char **argv) {
  //HEIKO char buffer[PIPE_BUFFER];  //buffer for reading/writing
  int int_array[2];

  pid_t myPid;            //variable for fork
  int parent_pipe[2];     //pipe for parent
  int children_pipe[2];   //pipe for children
  //type int[2], because we need one element for reading,
  //and the other one for writing. this is done because
  //the system call pipe() takes a single argument which is
  //an array of two integers.

  //now create those two mentioned pipes
  if (pipe(parent_pipe) < 0) {
    //pipe error when result of pipe(pipe_argument) is smaller 0
    printf("Error creating the pipe.\n");
    exit(1);
  }

  if (pipe(children_pipe) < 0) {
    //pipe error when result of pipe(pipe_argument) is smaller 0
    printf("Error creating the pipe.\n");
    exit(1);
  }

  //scan a string representing two integer numbers
  //we have to parse that string later in the child
  printf("Geben Sie die erste Zahl an:\n");
  scanf("%d", &int_array[0]);

  printf("Geben Sie die zweite Zahl an:\n");
  scanf("%d", &int_array[1]);

  myPid = fork();
  if (myPid < 0) {
    //if the result of fork() is smaller than 0 => error
    printf("Fork error\n");
    exit(1);
  }
  else if(myPid == 0) {      //if pipe create is success
    int x = 0;
    int y = 0;
    printf("Fork ok\n");
    read(parent_pipe[0], &x, sizeof(int));
    read(parent_pipe[0], &y, sizeof(int));
    printf("first: %d\n", x);
    printf("second: %d\n", y);
    //read(parent_pipe[0], buffer, sizeof(buffer));
    //printf("piped string: %s\n", x);
  }

  close(parent_pipe[0]);
  write(parent_pipe[1], &int_array[0], sizeof(int));
  write(parent_pipe[1], &int_array[1], sizeof(int));

  exit(0);
}
