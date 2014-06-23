#include <stdlib.h>
#include <stdio.h>
#include <string.h>  // for string operations
#include <sys/msg.h> //msgset() and msgrcv() + flag arguments

int main (int argc, char **argv) {

  //check if three parameters are given
  //im using value 3, because 1 is datafile, 2 & 3 & 4 for my parameters
  if (argc != 4) {
    printf("Usage: msgsend <key> <type> \"text of message\"\n");
    exit(1);
  }

  int key = atoi(argv[1]);
  int type = atoi(argv[2]);
  char *msg = argv[3];

  //placeholder for message id
  int msgid;

  //struct for a message
  typedef struct {
    long type;
    char text[50];
  } msg_struct;

  //create a struct of type msg_struct
  msg_struct message;
  //set the message type
  message.type = type;
  //copy msg to the message struct (variable: msg -> message.text)
  strcpy(message.text, msg);

  //flags for creating or getting the queue
  int msgflg = IPC_CREAT | 0666;
  //IPC_CREAT: create queue if it does not already exist
  //0666: make it readable and appendable to all

  //now create or get a message queue
  if((msgid = msgget(key, msgflg)) < 0) {
    perror("Error getting the requested queue");
    exit(1);
  }

  //now send the message
  //IPC_NOWAIT: 
  //50 = bufferlength
  //msgid = id of the message
  //msg = content of the message
  if (msgsnd(msgid, &message, 50, IPC_NOWAIT) < 0) {
    perror("Error sending the message");
    exit(1);
  }
  else {
    printf("\n---------------------------\n");
    printf("Message successfully sent. \n");
    printf("Key: %d\n", key);
    printf("Type: %ld\n", message.type);
    printf("Text: %s\n", message.text);
    printf("Queue ID: %d\n", msgid);
    printf("\n---------------------------\n");
  }

  exit(0);

}
