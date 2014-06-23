/* Task 8-2
 * The task in 8-2 was to write a filter program add2, which reads two
 * integers, calulates their sum print the sum afterwards. The main
 * programm should read two integer values from stdin and give those
 * numbers to a child process through a pipe. The child process has
 * to calculate the sum using predefined add2 function. After that,
 * the child sends the result back to the parent through another pipe.
 * Finally the parent process prints the final result to stdout.
 */

#include <stdlib.h>       //exit(0) included
#include <stdio.h>        //printf
#include <sys/types.h>    //for process id pid_t
#include <unistd.h>       //system api fork, write, read
#include <string.h>       //string library

#define PIPE_BUFFER 100

int main (int argc, char **argv) {
  //variable for my two integer values scanning with scanf
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
  else if(myPid == 0) {      //if fork is success
    int x = 0,
        y = 0,
        success = 0;         //looks if exec

    //every output of this fork process goes into the second pipe (children_pipe)
    dup2(children_pipe[1], STDOUT_FILENO);

    //reading the first parameter of the first pipe for later calculation
    read(parent_pipe[0], &x, sizeof(int));
    //reading the second parameter of the first pipe for later calculation
    read(parent_pipe[0], &y, sizeof(int));

    char charbuffer1[100];   //a char buffer for my first scanned integer value
    char charbuffer2[100];   //a char buffer for my second scanned integer value

    //in the following lines I have to use sprintf, in order to pass arguments to
    //my add2 function, because with execlp I can only pass arguments which are
    //characters

    //conversion from integer x to char charbuffer1
    sprintf(charbuffer1, "%d", x);
    //conversion from integer y to char charbuffer2
    sprintf(charbuffer2, "%d", y);

    //execute add2-filter program with execlp
    //program add2 needs to be in the same directory (already compiled)
    success = execlp("./add2", "./add2", charbuffer1, charbuffer2, NULL);

    //when success has value "-1", an error occured
    if (success == -1) {
      printf("Execlp error.\n");
    }

  }

  //close the children read pipe, because we perform only writes here
  close(parent_pipe[0]);
  //write the first scanned value to the first pipe
  write(parent_pipe[1], &int_array[0], sizeof(int));
  //write the second scanned value to the first pipe
  write(parent_pipe[1], &int_array[1], sizeof(int));

  //wait one second for child processes
  //sleep(1); Not nececessary

  //char string buffer for the redirected output of the child
  char sum[PIPE_BUFFER];

  //close the children write pipe, because we do not need it
  close(children_pipe[1]);
  //read from the children output pipe
  read(children_pipe[0], &sum, sizeof(sum));

  //finally print the sum to stdout
  printf("The sum is: %s\n", sum);


  exit(0);
}
