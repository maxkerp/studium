/*******************************************************************************
 * Author:  Maximilain Kerp
 * Group:   5
 * Date:    June 20th, 2014
 * Purpose: This program show the use of message queues and inter process
 *          communication.
 *
 * Usage:
 *
 * msgctrl -s <queue_id> <priotity> "message"
 *
 *    This command creates a queue with an id of <queue_id> if it doen't exist
 *    and sends the message "message" with priority <priority> to it.
 *
 * msgctrl -r <queue_id> <priority>
 *
 *    This command receives a message with a priority <priority>
 *    from the queue <queue_id>
 *
 ******************************************************************************/

//==============================================================================
// INCLUDES

#include <stdio.h>     // print()-family
#include <stdlib.h>    // exit(), EXIT_SUCCESS
#include <unistd.h>    // getopt()
#include <sys/types.h> // msgrcv(), msgsnd()
#include <sys/ipc.h>   //
#include <sys/msg.h>   //

//==============================================================================
// DEFINES
#define MSG_LEN 1024

//==============================================================================
// GLOBAL VARIABLES
int err;

//==============================================================================
// msg_t definition
typedef struct {
  long msg_type;      // Type of the message
  char *msg;  // The message itself
} msg_t;

//==============================================================================
// FUNCTION DECLARATIONS
int send_msg (int key, int type, char *message);
int rcv_msg (int key, int type);

//==============================================================================
// MAIN
int main (int argc, char **argv)
{
  opterr = 1;
  // opt will be set to the option argument by getopt()
  int opt;

  if (argc == 1) {
    printf("Usage: %s [-r key type] [-s key type \"message\"]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  while ( (opt = getopt(argc, argv, "s:r:")) != EOF ) {

    switch (opt) {
      case 's': send_msg(atoi(argv[optind - 1]), atoi(argv[optind]),
                    argv[optind + 1]);
                break;
      case 'r': rcv_msg(atoi(argv[optind - 1]), atoi(argv[optind]));
                break;
      default:  fprintf(stderr, "Usage: %s [-r key type] " \
                    "[-s key type \"message\"]\n",argv[0]);
                exit(EXIT_FAILURE);
    }
  }

  exit(EXIT_SUCCESS);
}

//==============================================================================
// This function sends a <messge> with a priority of <type> to the queue with
// the id of <key>. The queue will be created, if it doesn't exists.
int send_msg (int key, int type, char *message)
{
  int msg_id;

  msg_t msg = {.msg_type=type, .msg=message};

  // Create or get the message queue and return the msg_id
  if( (msg_id = msgget(key, IPC_CREAT | 0666)) == -1) {
    perror("Error getting queue");
    exit(EXIT_FAILURE);
  }

  printf("msg_id: %d\n", msg_id);

  // Send message to the queue, wait if queue is full (NULL)
  if ( (err = msgsnd(msg_id, &msg, MSG_LEN, 0)) == -1 ) {
    perror("Error sending message to queue");
    exit(EXIT_FAILURE);
  }

  printf("Message send successfully to queue with key: %d\n", key);

  return 0;
}

//==============================================================================
// This function receives a message from the queue with an id of key and a
// priority of type.
int rcv_msg (int key, int type)
{
  int msg_id;
  msg_t msg;

  // Get msg_id for given key
  if ( (msg_id = msgget(key, 0)) == -1) {
    perror("Error getting queue");
    exit(EXIT_FAILURE);
  }

  // Receive message from queue
  if ( (err = msgrcv(msg_id, &msg, MSG_LEN, type, IPC_NOWAIT)) == -1 ) {
    perror("Error receiving message");
    exit(EXIT_FAILURE);
  }

  printf("Message received successfully from queue with key: %d\n" \
      "MESSAGE: %s", key, msg.msg);

  return 0;
}
