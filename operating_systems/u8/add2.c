#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main( int argc, char **argv)
{
  //read two ints from stdin
  char arg1[11], arg2[11];
  read(0, &arg1, sizeof(char[11]));
  read(0, &arg2, sizeof(char[11]));

  // convert and compute the sum
  int a = atoi(arg1);
  int b = atoi(arg2);
  int sum = a + b;

  // print it to stdout
  printf("%d\n", sum);

  return 0;
}
