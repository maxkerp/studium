#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {

  //if one argument is not given, exit program
  //argv[1] is the filename
  if (argc != 2) {
    printf("Missing argument\n");
    exit(1);
  }

  //parse the given flight id for later decrementation
  int i_id = atoi(argv[1]);
  //integer for reading the flightid
  int flightid;
  //character for skipping the divider character
  char divider = '-';
  //integer for reading the available flight seats
  int i_seats;
  //char array for setting the filename
  char filename[] = "seatlist.txt";
  //integer for file descriptor of seatlist.txt
  int seatfile;
  //char for skipping the end-of-data-line character
  char endofline = '!';

  //integer for checking success/error of read/write
  //only one variable needed, because read() and write() return
  //integer values (-1 for error)
  int result;

  //try to open the file
  //O_RDWR: flag for read-only
  if ((seatfile = open(filename, O_RDWR)) == -1) {
    //if no success, throw error using perror
    perror("Error while opening the file.");
  }

  //infinite loop until the given flight id is found,
  //or function read() gets no result
  while (1) {

    //try to read the first parameter from 
    if ((result = read(seatfile, &flightid, sizeof(flightid))) == -1 ) {
      perror("Error while reading the file.");
    }
    //if end of file is reached, exit program
    else if (result == 0) {
      printf("Reached end of file. Exit.\n");
      exit(1);
    }

    //SEEK_CUR = cursor flag for the current position, also there are cursor flags for
    //absolute positioning and positioning relatively to the end of the file.
    //if current position not matches the given flight id
    if (i_id != flightid) {
      //set the cursor to the next data-set. in order to do this, the cursor have
      //to skip the upcopming divider ('-'), the available seats (i_seats) and
      //the end of line character ('!').
      lseek(seatfile, sizeof(divider) + sizeof(i_seats) + sizeof(endofline), SEEK_CUR);
    }
    //if current position matches the given flight id
    else {
      //skip the divider with lseek()
      lseek(seatfile, sizeof(divider), SEEK_CUR);

      //lock the section for exlusive access to the file
      lockf(seatfile, F_LOCK, sizeof(i_seats));

      if ( (result = read(seatfile, &i_seats, sizeof(i_seats))) == -1 ) {
        perror("Read error.");
      }

      //sleep for one second
      sleep(1);
      //decrement the current seat size on current position
      i_seats -= 1;
      //now move the cursor backwards to the beginning of i_seats and write the
      //new decremented value.
      lseek(seatfile, -sizeof(i_seats), SEEK_CUR);

      //if there was an write error, use perror
      if ((result = write(seatfile, &i_seats, sizeof(i_seats))) == -1 ) {
        perror("Write error.");
      }

      //unlock the file after operations are finished
      lockf(seatfile, F_ULOCK, sizeof(i_seats));

      //close the file when unlock is done
      if ((result = close(seatfile)) == -1) {
        //throw a error using perror if closing was not successful
        perror("Close error.");
      }

      exit(0);
    }
  }
}
