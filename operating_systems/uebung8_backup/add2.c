/* Filter add2
 * 
 * This is the filter for calculating a sum of two integer
 * values.
 */

//this file is my needed add2 filter method which prints
//the result of an addition to the stdout

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {

  //variables for my two scanned int variables and also 
  //another int variable for my addition sum
  int x = 0;
  int y = 0;
  int sum = 0;

  if (argc < 2) {
     // we have not enough args for calculating
     // breaking up
     exit(1);
  }

  //atoi is a function. it parses a c-string to a number.
  //the type of the returned value is int.
  x = atoi(argv[1]);
  y = atoi(argv[2]);

  //calculate the sum...
  sum = x + y;

  //... andprint sum of x and y to stdout
  printf("%d", sum);

  exit(0);
}
