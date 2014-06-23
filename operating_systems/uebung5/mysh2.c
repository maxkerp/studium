#include <stdio.h> //exit
#include <stdlib.h> //printf
#include <unistd.h>  // for pids
#include <string.h> //strings
#include <sys/types.h> //fork
#include <fcntl.h>  //file descriptors

int main(int argc, const char *argv[]) {

  int fd;

  int bytes_read; // buffer
  int nbytes = 100; // size of buffer
  char *input; // string pointer
  input = (char *) malloc (nbytes + 1);
  pid_t mypid;

  if (argc != 2) {
    //if arg is missing
    printf("args missing");
    exit(1);
  }
  //create file if not available, if file -> truncate, chmod read
  if ((fd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0644)) < 0) {
    printf("file error\n");
    exit(1);
  }

  int defout = dup(1); //creates copy of the current fd
  dup2(fd, 1);

  mypid = fork();
  if (mypid < 0) {
    close(fd);
    printf("fork error\n");
    exit(1);
  }
  else if (mypid == 0) {
    bytes_read = getline (&input, &nbytes, stdin);
    // if string, remove line break and change to \0
    if (input != NULL) {
      size_t last = strlen (input) - 1;
      if (input[last] == '\n') {
        input[last] = '\0';
      }
    }
    printf("%s\n", input);
    execlp (input, input, NULL);
    exit(0);
  }

  waitpid(mypid, 0, 0); //wait for forks

  dup2(defout, 1); // redirect output back to stdout
  printf("redirected output: \n");

  //read from file and write to stdout
  int c;
  FILE *file;
  file = fopen(argv[1], "r");
  if (file) {
    while ((c = getc(file)) != EOF)
    putchar(c);
    fclose(file);
  }

  printf("\nprogram exit\n");
  close(fd);
  close(defout);
  exit(0);
}
