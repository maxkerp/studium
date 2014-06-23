#include <stdlib.h>
#include <stdio.h>
#include <sys/msg.h> // for msgget() and msgrcv() functions

int main (int argc, char **argv) {

  //check if two parameters are given
  //im using value 2, because 1 is datafile, 2 & 3 for my parameters
  if (argc != 3) {
    printf("Usage: msgsrcv <key> <type> \n");
    exit(1);
  }

  int key = atoi(argv[1]);
  int type = atoi(argv[2]);

  //placeholder for id
  int msgid;

  //struct for a message
  typedef struct {
    long type;
    char text[50];
  } msg_struct;

  msg_struct message;

  // Get the id from the given (int) key
  // first parameter: key
  // second parameter: special flags for msgget, not needed here

  // The argument msgflg specifies the action to be taken if one or more of the following are true:
  // 1. The number of bytes already on the queue is equal to msg_qbytes.
  // 2. The total number of messages on all queues system-wide is equal to the system-imposed limit.
  // => Available actions are: Sending the message or throw an error
  if ((msgid = msgget(key, 0)) < 0) {
    perror("Error getting the queue");
    exit(1);
  }

  //1. parameter: queue id
  //2. parameter: location to write the message
  //3. parameter: size of the message in bytes
  //4. parameter: type of the message
  //5. parameter: flag IPC_NOWAIT: if no messages are available the function returns a ENOMSG. if
  //this flag is not passed, the msgrcv function blocks until a message gets into the queue
  //receive the message from the queue
  if (msgrcv(msgid, &message, 50, type, 0) == -1) {
    perror("Error receiving the message.");
    exit(1);
  }

  printf("-----------------------------\n");
  printf("Received the message\n:");
  printf("Key: %d\n:", key);
  printf("Type: %d\n:", type);
  printf("Message: %s\n:", message.text);
  printf("-----------------------------\n");
  exit(0);

}
