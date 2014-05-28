#include <stdio.h>
#include <stdlib.h>

int main( int argc, char **argv)
{
  if ( argc != 3)
    printf("usage: add2 arg1 arg2 ");

  int arg1 = atoi(argv[1]);
  int arg2 = atoi(argv[2]);

  int sum = arg1 + arg2;

  printf("arg1 = %i, arg2 = %i\n", arg1, arg2);
  printf("Sum is: %i\n", sum);


  return 0;
}
