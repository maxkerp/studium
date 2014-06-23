#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h> //filesize

int main(int argc, char **argv) {

  //integer for flightid
  int flightid;
  //char for divide flightid and seats in data-line to write
  char divider = '-';
  //indicator for end-of-data-line
  char endofline = '!';
  //integer value for available seats
  int i_seats;
  //char array for filename
  char filename[] = "seatlist.txt";
  //file descriptor for file
  int seatfile;
  int filesize;

  //open the file with read-only permission
  seatfile = open (filename, O_RDONLY);

  //use stat function from sys/stat header file to get the
  //total file size. the file size is needed for the iterations
  //through my stored data-sets.
  struct stat st;
  stat(filename, &st);
  //filesize = size of the file in bytes
  filesize = st.st_size;

  //calculate the size in bytes of one complete stored data-set
  int entrySize = sizeof(flightid)+sizeof(divider)+sizeof(i_seats)+sizeof(endofline);

  //set cursor to the beginning of the file
  lseek (seatfile, 0, SEEK_SET);

  //iterate through the file until end of the file is reached. im using filesize/entrysize
  //to check if end is reached.
  for (int i = 1; i <= filesize/entrySize; i++) {
    //read all parameters: 1. flight id, 2. char divider, 3. available seats
    //4. end of data-line character
    read (seatfile, &flightid, sizeof(flightid));
    read (seatfile, &divider, sizeof(divider));
    read (seatfile, &i_seats, sizeof(i_seats));
    read (seatfile, &endofline, sizeof(endofline));

    //print all information to stdout
    printf("FlightID: %d %c Available Seats: %d %c \n", flightid, divider, i_seats, endofline);
  }

  //close the file
  close (seatfile);

  return 0;
}
