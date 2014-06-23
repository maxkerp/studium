//################################################################################
//## Matrikelnummer: 9019307                                                    ##
//## Gruppe: 5                                                                  ##
//## Erstellungsdatum: 29.05.2014                                               ##
//## Funktionsumfang A:                                                         ##
//## Aufgabenblatt: 8 (8-1 u. 8-2)                                              ##
//## Info: Doppelseitig bedruckt                                                ##
//################################################################################

/* Task 8-1
 * The Task in 8-1 is to create a child process (fork) and send
 * a string to the child through a so called pipe. After that
 * process the string is printed out.
 */

#include <stdlib.h>       //exit(0) included
#include <stdio.h>        //printf
#include <sys/types.h>    //for process id pid_t
#include <unistd.h>       //system api fork, write, read
#include <string.h>       //string library

#define PIPE_BUFFER 100

int main (int argc, char **argv) {

  pid_t myPid;               //variable for fork
  int pipe_argument[2];      //pipe arguments

  //type int[2], because we need one element for reading,
  //and the other one for writing. this is done because
  //the system call pipe() takes a single argument which is
  //an array of two integers. the first value is for reading,
  //the second one is for writing.

  char buffer[PIPE_BUFFER];  //buffer for reading/writing
  char *myString = "hello world";

  //create the pipe. exit programm if creation of the pipe
  //was not successful.
  if (pipe(pipe_argument) < 0) {
    //pipe error when result of pipe(pipe_argument) is smaller 0
    printf("Error creating the pipe.\n");
    exit(1);
  }

  myPid = fork();            //create the fork process
  if (myPid < 0) {
    //if the result of fork() is smaller than 0 => error
    printf("Fork error\n");
    exit(1);
  }
  else if(myPid == 0) {      //if pipe create is success
    //here we are in our child process

    close(pipe_argument[1]);
    //if the parent wants to send data to the child, we have to
    //close pipe_argument[0]. The child has to close pipe_argument[1].

    //read a string from pipe
    read(pipe_argument[0], buffer, sizeof(buffer));
    printf("piped string: %s\n", buffer);
  }

  close(pipe_argument[0]);
  //if the parent wants to send data to the child, we have to
  //close pipe_argument[0]. The child has to close pipe_argument[1].

  //send "myString" through the output side of pipe
  write(pipe_argument[1], myString, (strlen(myString)+1));
  //strlen mystring+1 because of end of string extension

  exit(0);
}

