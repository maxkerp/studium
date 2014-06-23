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

int main (int argc, char **argv) {

  //if too less arguments, exit program
  if (argc != 3) {
    printf("Not enough information.\n");
    exit(1);
  }

  //int value for total flights
  int total_flights = atoi(argv[1]);
  //int value for available seats
  int available_seats = atoi(argv[2]);

  char filename[] = "seatlist.txt";

  int fd;         //file descriptor (int), for later return value from open()
  int fdclose;    //return status of close()

  //this character is for dividing the flight number and the remaining
  //seats in the seatfile.
  char divideSymbol = '-';
  //this character shows the end of the data-line for flight number
  //and remaining seats in the seatfile.
  char endOfLine = '\n';

  //open the file with open()
  //O_RDWR = flag for read and write
  //O_CREAT = flag for creating the file if not existing
  if ((fd = open(filename, O_WRONLY | O_CREAT, O_TRUNC) == -1)) {
    //throw perror
    perror("Error opening seatfile...\n");
    //exit program with error status
    exit(1);
  }


  //here is the location to write into the initial seatfile
  char my_write_str[] = "1234567890";
  char my_read_str[100];

  /* Write 10 bytes of data and make sure it's written */
  write (fd, (void *) my_write_str, 10);
  fsync (fd);

  /* Seek the beginning of the file */
  lseek (fd, 0, SEEK_SET);

  /* Read 10 bytes of data */
  read (fd, (void *) my_read_str, 10);

  /* Terminate the data we've read with a null character */
  my_read_str[10] = '\0';

  sleep(1);
  printf ("String read = %s.\n", my_read_str);

  //close the file
  if ((fdclose = close(fd)) == -1) {
    //exit program with error status if close was unsuccessful
    perror("Error closing seatfile.\n");
    exit(1);
  }

  //exit program
  exit(0);
}
