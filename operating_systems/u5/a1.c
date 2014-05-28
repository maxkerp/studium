/*******************************************************************
 * Author:    Maximilian Kerp
 * Date  :    12.05.2014
 * Purpose:   Learn and understand file descriptors in unix
 *
 * What does this program do:
 *
 * This program creates a shell which reads from STDIN creates a
 * a subprocess which executes the command using exec() and writes
 * out to STDOUT using a file descriptor.
 *
 ******************************************************************/
#define MAX 50

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

 int main (int argc, char **argv)
 {
   int fd[2]; // array of file descriptors
   pid_t childpid = NULL; // childprocess
   void *buffer = calloc(MAX, sizeof(char));
   char string[] = "Hi there!\n";

   pipe(fd); // create pipe

   if ( (childpid = fork()) == -1)
   {
      perror("fork");
      exit(1);
   }

   if(childpid == 0){

     // close exit of pipe
     close(fd[1]);

     // read string in pipe
     read(fd[0], buffer, sizeof(buffer));
     printf("read: %s\n", buffer);

   }
   else
   {
    //close entrance of pipe
    close(fd[0]);

    //send string through pipe
    write(fd[1], string, (strlen(string)+1));
   }

   return 0;
 }