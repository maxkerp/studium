//################################################################################
//## Name: Heiko Kernbach                                                       ##
//## Matrikelnummer: 9019307                                                    ##
//## Gruppe: 5                                                                  ##
//## Erstellungsdatum: 14.06.2014                                               ##
//## Funktionsumfang A: Sperren von Dateien                                     ##
//## Aufgabenblatt: Uebung 12                                                   ##
//## Info: Doppelseitig bedruckt                                                ##
//################################################################################

/* Task 12
 * The task was to create a file (seatfile) which cotains data about a flight. Each
 * data-set contains a flight-number and the remaining available seats. The second
 * task is to manage this file with following options: Read the file, find the
 * correct data in this file, read current available seats, reduce available seats
 * and write the updated correct seat number back to the file. The programm needs
 * to wait one second (sleep(1)) before reading and writing the file. Also it should
 * be secure when multiple access to the file exist (lock).
 */

/* sellseat.c */

#include <stdio.h>   // exit(0) included
#include <stdlib.h>  // printf
#include <fcntl.h>   // open() & defined flags O_CREATE, O_WRONLY ...
#include <unistd.h> // for close()

//functions to use: open(), perror(), lseek(), lockf(), read(), sleep(), write()

#define SEATFILE "seatfile"

int main (int argc, char **argv) {

  int fd;         //file descriptor (int), for later return value from open()
  int fdclose;    //return status of close()
  int lockFile;   //return status of lock()
  int readStatus; //return status of read()
  ssize_t bytes_written; //written bytes to file through write()

  //this character is for dividing the flight number and the remaining
  //seats in the seatfile.
  char divideSymbol = '-';
  //this character shows the end of the data-line for flight number
  //and remaining seats in the seatfile.
  char endOfLine = "\n";

  //open the file with open()
  //O_RDWR = flag for read and write
  //O_CREAT = flag for creating the file if not existing
  if ((fd = open(SEATFILE, O_RDWR | O_CREAT) == -1)) {
    //throw perror
    perror("Error opening seatfile...\n");
    //exit program with error status
    exit(1);
  }

  printf("File opened...\n");

  //try to get the exclusive access to the file
  //F_LOCK flag for locking the file
  while ((lockFile = lockf(fd, F_LOCK, 0)) == -1) {
    printf("Already locked. Waiting for unlock\n");
  }
  printf("File is now locked.\n");

  //here is the location to write into the initial seatfile

  


  //try to unlock the file after finished with file
  //F_ULOCK flag for unlocking the file
  if ((lockFile = lockf(fd, F_ULOCK, 0)) == -1) {
    //throw error and close file descriptor if unlock not working
    perror("Unlock failure.\n");
    close(fd);
    exit(1);
  }
  printf("File is now unlocked.\n");



  //close the file
  if ((fdclose = close(fd)) == -1) {
    //exit program with error status if close was unsuccessful
    perror("Error closing seatfile.\n");
    exit(1);
  }
  printf("File closed.\n");

  //exit program
  printf("Exiting.\n");
  exit(0);
}
