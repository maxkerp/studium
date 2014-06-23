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

#define SEATFILE "seatfile.txt"

int main (int argc, char **argv) {

  int seat_read = 0;  //int for reading the seat size
  int flight_read = 0;  //int for reading the flight id

  int fd;         //file descriptor (int), for later return value from open()
  int fdclose;    //return status of close()

  //open the file with open()
  //O_RDONLY flag for read only file permission
  if ((fd = open(SEATFILE, O_RDONLY) == -1)) {
    //throw perror
    perror("Error opening seatfile...\n");
    //exit program with error status
    exit(1);
  }

  printf("File opened...\n");
  printf("Reading file...\n");

  int bytes_written;

  //infinite loop for reading
  while (1) {

    //first read the first parameter of the seat file
    if ((bytes_written = read(fd, &seat_read, sizeof(int))) == -1) {
      perror("Error reading first parameter.");
    }
    else if (bytes_written == 0) {
      break;
    }

    //jump to the positioned divider to read our second argument
    lseek(fd, sizeof(char), SEEK_CUR);

    //now read the second parameter of the seat file
    if ((bytes_written = read(fd, &flight_read, sizeof(int))) == -1) {
      perror("Error reading second parameter.");
    }
    else if (bytes_written == 0) {
      break;
    }

    //now jump to the end of the line
    lseek(fd, sizeof(char), SEEK_CUR);

    printf("Flight ID: %d, Seats: %d \n", flight_read, seat_read);
  }

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
