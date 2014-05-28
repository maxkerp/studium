#include <stdio.h>

int main( int argc, char **argv){

  int a, b;

  scanf("%d", &a);
  scanf("%d", &b);

  printf("Gelesen: a: %d b: %d\n", a, b);

  int sum = a + b;
  printf("Summe ist %d\n", sum);

  return 0;
}
