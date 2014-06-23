//this file is my needed add2 filter method which prints
//the result of an addition to the stdout

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {

  int x, y;
  //scan a string representing two integer numbers
  //we have to parse that string later in the child
  printf("Geben Sie die erste Zahl an:\n");
  scanf("%d", &x);

  printf("Geben Sie die zweite Zahl an:\n");
  scanf("%d", &y);

  //print sum of x+y to stdout
  printf("%d", x+y);

  exit(1);
}
