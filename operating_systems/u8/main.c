/*************************************************************************
 * Author:  Maximilain Kerp
 * Group:   5
 * Date:    31.05.14
 * Purpose: The goal of this programm was to inter-process cummunication
 *          using pipes. The parent reads in two integers from the
 *          keyboard and writes it to a pipe(parent_child). The child let's the
 *          read end of parent_child become the stdin for it's own process and
 *          let's stdout be the write end of another pipe to the parent (child_parent).
 *          After that, the child executes a programm which reads in two
 *          integers from stdin and writes out to stdout. At last the parent
 *          reads from the pipe coming from the child (child_parent) and prints out
 *          whatever the program has written to stdout.
 ***************************************************************************/
#include <stdio.h>        // printf(), fprintf(), scanf(), fscanf()
#include <unistd.h>       // fork(), read(), write(), pipe(), dup2()

int main( int argc, char **argv)
{
  //===========================================================
  // needed variables
  pid_t pid;            // pid of child process
  FILE *parent_read,*parent_write; // file streams needed to use stdio on pipes
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
  // we let parent_child[0] be stdin for this process and
  // child_parent[1] be stdout.
  if(!pid){

    // we're just reading from this pipe, so close it's write end
    close(parent_child[1]);

    // everything read from stdin in this process
    // will come from parent_child[0]
    dup2(parent_child[0], STDIN_FILENO);

    // everything written to stdout in this process
    // will go to child_parent[1]
    dup2(child_parent[1], STDOUT_FILENO);

    // execute add2, it will now read from parent_child[0]
    // instead of stdin and write to child_parent[1] instead
    // of stdout
    int i = execl("./add2", "./add2", NULL);
    if(i == -1)
      printf("ERROR executing\n");

  }

  // Here we are in the parent process. We read two ints from the
  // keyboard and write them to parent_child[1].
  // At last we read from child_parent[0] and print its content
  // to stdout which is now the terminal.

  // we're just writing to this pipe, so close it's read end.
  close(parent_child[0]);

  // we're just reading from this pipe, so close it's write end
  close(child_parent[1]);

  int a,b,sum;

  // read two ints from stdin
  scanf("%d %d", &a, &b);

  // open file streams of the pipe so we can use fprintf and
  // fscanf on the pipe.
  parent_write = fdopen(parent_child[1], "w");
  parent_read = fdopen(child_parent[0], "r");

  // write to parent_child and close
  fprintf(parent_write, "%d %d", a,b);
  fclose(parent_write);

  // read from child_parent and print to stdout
  fscanf(parent_read, "%d", &sum);
  printf("SUM: %d\n", sum);

  return 0;
}
