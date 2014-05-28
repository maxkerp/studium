#include <stdio.h>
#include <unistd.h>

int main( int argc, char **argv)
{
  //===========================================================
  // needed variable
  pid_t pid;            // pid of child process
  int parent_child[2];  // pipe from parent to child
  int child_parent[2];  // pipe from child to parent


  // create pipes, abort when error
  if(pipe(parent_child) == -1)
    printf("ERROR creating pipe");

  if(pipe(child_parent) == -1)
    printf("ERROR creating pipe");

  // creating child process
  pid = fork();
  if(pid == -1)
    printf("ERROR forking\n");

  // Now we are in the child process.
  // We need to read the 2 ints from parent_child[0], give them to
  // execl as arguments for add2 and map stdout to child_parent[1]
  // since add2 writes to stdout, but we want it to write back to the
  // parent.
  if(!pid){
    // we don't write to that
    close(parent_child[1]);

    // everything written to stdout will go to cp[1]
    dup2(child_parent[1], 1);

    // read two ints from pc_pipe
    int i1, i2;
    fscanf(parent_child[0], "%d", &i1);
    fscanf(parent_child[0], "%d", &i2);

    // convert ints to strings
    char *arg1, *arg2;
    sprintf(arg1, "%d", i1);
    sprintf(arg2, "%d", i2);

    // execute add2 with the (converted) ints from the pipe pc
    // add will wrtite to stdout which is now cp[1]
    int i = execl("./add2", "./add2", arg1, arg2, NULL);
    if(i == -1)
      printf("ERROR executing\n");

  }

  // Here we are in the parent process. We read to ints from the
  // keyboard. Write them to the pipe. Then we read the answer from
  // cp_pipe and write it to stdout (terminal)

  // we don't read from that
  close(parent_child[0]);

  // we don't write to that
  close(child_parent[1]);

  // read two ints from the keyboard
  int arg1, arg2;       // args to send to child
  scanf("%d", &arg1);
  scanf("%d", &arg2);

  // write to the pc_pipe
  fprintf(parent_child[1], "%d", arg1);
  fprintf(parent_child[1], "%d", arg2);

  // read answer from cp_pipe
  int sum;
  fscanf(child_parent[0], "%d", &sum);

  // write answer to the terminal
  printf("Sum: %d", sum);

  return 0;
}
