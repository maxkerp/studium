/**********************************************************
 * Author:  Maximilian Kerp
 * Group:   5
 * Date:    31.05.14
 * Purpose: Read in two integers from stdin compute the sum
 *          and print the sum to stdout.
 **********************************************************/
#include <stdio.h>      // printf()

int main( int argc, char **argv)
{
  //read two ints from stdin
  int a,b;
  scanf("%d %d", &a, &b);

  // compute the sum
  int sum = a + b;

  // print sum to stdout
  printf("%d\n", sum);

  return 0;
}
