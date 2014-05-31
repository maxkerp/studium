/**********************************************************
 * Author:  Maximilian Kerp
 * Group:   5
 * Date:    31.05.14
 * Purpose: Read in two integers from stdin compute the sum
 *          and print the sum to stdout.
 **********************************************************/
#include <stdio.h>      // printf()
#include <stdlib.h>     // atoi()
#include <unistd.h>     // read()


int main( int argc, char **argv)
{
  //read two ints from stdin
  char arg1[11], arg2[11];
  read(STDIN_FILENO, &arg1, sizeof(char[11]));
  read(STDIN_FILENO, &arg2, sizeof(char[11]));

  // convert ints and compute the sum
  int a = atoi(arg1);
  int b = atoi(arg2);
  int sum = a + b;

  // print sum to stdout
  printf("%d\n", sum);

  return 0;
}
