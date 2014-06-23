#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

//this is the testprogram to create and receive messages from system queue
int main (int argc, char **argv) {

  //placeholder for result of my system() function calls
  int res1, res2, res3, res4;

  //now create the messages
  res1 = system("./sendmessage 100 4 Hallo1");
  res2 = system("./sendmessage 100 8 Hallo2");
  res3 = system("./sendmessage 100 9 Hallo3");
  res4 = system("./sendmessage 100 7 Hallo4");

  if (res1 != 0 || res2 != 0 || res3 != 0 || res4 != 0) {
    printf("error creating messages\n");
  }
  else {
    printf("All 4 messages created.\n");
  }

  //now check if the messages are really created using systems ipcs.
  //count should be 4
  printf("\n--------------   IPCS   -------------\n");
  system("ipcs -a");

  //now receive the created messages
  system("./receivemessage 100 9");
  system("./receivemessage 100 4");
  system("./receivemessage 100 8");

  //check if receiving the messages was successful
  if (res1 != 0 || res2 != 0 || res3 != 0) {
    printf("error receiving messages\n");
  }
  else {
    printf("All 3 messages received.\n");
  }

  //now check if the messages are really received using systems ipcs
  //count now should be 1
  printf("\n--------------   IPCS   -------------\n");
  system("ipcs -a");

  exit(0);
}
