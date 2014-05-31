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
    //DEBUG
    // we don't write to that
    close(parent_child[1]);

    // everything written to stdout will go to cp[1]
    dup2(child_parent[1], 1);

    // DEBUG: read one int
    //int a,b;
    //read(parent_child[0], &a, sizeof(int));
    //read(parent_child[0], &b, sizeof(int));
    //printf("before exec: a:%d, b:%d\n", a,b);
    //close(parent_child[0]);

    // everything read from stdin will come from pc[0];
    dup2(parent_child[0], 0);


    // execute add2 with the (converted) ints from the pipe pc
    // add will wrtite to stdout which is now cp[1]
    int i = execl("./add2", "./add2", NULL);
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
  char arg1[11], arg2[11];       // args to send to child
  read(0, &arg1, sizeof(char[11]));
  read(0, &arg2, sizeof(char[11]));

  // write to the pc_pipe and close
  write(parent_child[1], &arg1, sizeof(char[11]));
  write(parent_child[1], &arg2, sizeof(char[11]));
  close(parent_child[1]);

  // everything coming from child_parent should go to stdoud
  char sum[11];
  read(child_parent[0], &sum, sizeof(char[11]));
  printf("SUM: %s\n", sum);

  return 0;
}
