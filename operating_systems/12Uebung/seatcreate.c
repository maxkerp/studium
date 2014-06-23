#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {

  //check if needed two arguments are given
  //if not, exit program.
  if (argc != 3) {
    printf("Not enough arguments\n");
    exit(1);
  }

  //parse the two given parameters as char and int
  //(char only for readability)
  char *flights = argv[1];
  char *seats = argv[2];
  int i_flights = atoi(flights);
  int i_seats = atoi(seats);

  //char array for filename
  char filename[] = "seatlist.txt";
  //integer for file descriptor
  int seatfile;
  //char for divider char
  char divider = '-';
  //char for end of data-line-char
  char endofline = '!';

  //open the file
  //O_RDWR = read and write flag permission
  //O_CREAT = if file not exists, create it
  //O_TRUNC = set the bytes size of the file to zero is file exists (cleanup)
  seatfile = open (filename, O_RDWR | O_CREAT | O_TRUNC);

  //now write the dataset until counter i_flights is reached
  for (int i = 1; i < i_flights; i++) {
    //write all four needed variables. the first one is the flight id, the second
    //is just a divider for readability and later parsing, the third is value for
    //the available seats and the last one is just a char indicator that after that
    //symbol there starts a new storage-dataset.
    write (seatfile, &i, sizeof(i));
    write (seatfile, &divider, sizeof(divider));
    write (seatfile, &i_seats, sizeof(i_seats));
    write (seatfile, &endofline, sizeof(endofline));
  }

  //after write is finished, close the file
  close (seatfile);

  //exit program
  return 0;
}
