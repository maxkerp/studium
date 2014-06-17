/*******************************************************************************
 * Author:  Maximilain Kerp
 * Group:   5
 * Date:    June 14th, 2014
 * Purpose: This program shows the use of lseek() and
 *          lockf().
 *
 * Usage:
 *
 * seats -c <num_flights> <initial_seats>
 *
 *    This command creates a file flightseats.txt
 *    in which it writes num_flights amount of data
 *    pairs with the initial seats amount of
 *    initial_seats_num
 *
 * seats -l
 *
 *    prints out a list of all flights and the
 *    available seats.
 *
 * seats -s <flight_number>
 *
 *    sells one seat from flight <flight_number>
 *
 ******************************************************************************/

//==============================================================================
// INCLUDES

#include <stdio.h>     // fopen(), perror()
#include <stdlib.h>    // exit(), EXIT_SUCCESS
#include <unistd.h>    // write(), read(), lseek(), lockf(), sleep(), getopt()
#include <sys/types.h> // lseek()
#include <fcntl.h>     // for FLAGS O_WRONLY in open()

//==============================================================================
// GLOBAL VARIABLES
int err, seatfile;
char divider, cr;

//==============================================================================
// FUNCTION DECLARATIONS
int create_seats (int n_flights, int n_seats);
int list_seats (void);
int sell_seat (int flight_id);

//==============================================================================
// MAIN
int main (int argc, char **argv)
{
  // telling getopts not to throw errors, we handle that ourselves
  opterr = 0;
  // opt will be set to the option argument by getopt()
  int opt;

  while ( (opt = getopt(argc, argv, "c:s:l")) != EOF ) {

    switch (opt) {
      case 'c': create_seats(atoi(argv[optind - 1]), atoi(argv[optind]));
                break;
      case 'l': list_seats();
                break;
      case 's': sell_seat(atoi(argv[optind - 1]));
                break;
      default:  fprintf(stderr, "Usage: %s [-c flights seats] [-l] [-s flight]\n",
                    argv[0]);
                exit(EXIT_FAILURE);
    }
  }

  exit(EXIT_SUCCESS);
}

//==============================================================================
// Function create_seats
// This function will write n_flights amount of data sets to the file
// seatfile.txt with an inital value of n_seats for seats. It will create the
// File if it doesn't exist
int create_seats (int n_flights, int n_seats)
{
  // Variables  declared in this function
  mode_t mode;

  printf("Creating %d data sets with an initial number of %d seats ...\n",
      n_flights, n_seats);

  // The mode (permission) for the file to create.
  mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
  // Open a file and receive the file descriptor, create if it doesn't exist.
  seatfile = open("seatfile.txt", O_WRONLY | O_CREAT, mode);
  if (seatfile == -1)
    perror("Error opening or creating seatfile.txt");

  // The divider we're using to divide the data sets
  divider = ' ';
  // The token we're using to mark the end of a line
  cr = '\n';

  // Now we create a loop in which we write the data sets in the following format
  //   flight_id<divider>n_seats<CARRIAGE RETURN>
  // everytime we read we need to check if we're at the end of the fiel (EOF/0).
  // We use the index i for flight_id
  for ( int i = 1; i <= n_flights; i++) {
    write(seatfile, &i, sizeof(i));
    write(seatfile, &divider, sizeof(divider));
    write(seatfile, &n_seats, sizeof(n_seats));
    write(seatfile, &cr, sizeof(cr));
  }

  if ( (err = close(seatfile)) == -1 )
    perror("Error closing seatfile.txt");

  return 0;

}

//==============================================================================
// Function list_seats
// This Function reads in all the data sets from the seatfile.txt and prints
// them out to STDOUT. If we read EOF we're done and break out of the loop
// close the file and return 0
int list_seats (void)
{
  int n_flights, n_seats;

  // We don't need a mode, since we're not creating any file. To keep the code
  // shorter we directly test for an error
  if ( (seatfile = open("seatfile.txt", O_RDONLY)) == -1 )
    perror("Error opening seatfile.txt");

  while (1) {
    // Read n_flights from textfile.txt. Break out of loop if EOF is
    // read, throw an error if one occurs
    if ( (err = read(seatfile, &n_flights, sizeof(n_flights))) == -1 )
      perror("Error reading seatfile.txt");
    else if (err == 0)
      break;

    // Use lseek to "jump" over the divider
    lseek(seatfile, sizeof(divider), SEEK_CUR);

    // Read n_seats from textfile.txt. Break out of loop if EOF is
    // read, throw an error if one occurs
    if ( (err = read(seatfile, &n_seats, sizeof(n_seats))) == -1 )
      perror("Error reading seatfile.txt");
    else if (err == 0)
      break;

    // use lseek to "jump" over cr
    lseek(seatfile, sizeof(cr), SEEK_CUR);

    // Print to STDOUT
    printf("Flight %d: %d seats available\n", n_flights, n_seats);
  }

  if ( (err = close(seatfile)) == -1)
    perror("Error closing seatfile.txt");

  return 0;
}

//==============================================================================
// Function sell_seat
// This Function sells one seat one flight with an id of flight_id. It loops
// through the flight_ids in seatfile.txt. If it reads the right flight_id
// it locks the section of the file which holds the n_seats value with lockf(),
// reads n_seats, decrements it and writes it back to the right position.
int sell_seat (int flight_id)
{
  int n_flights, n_seats;

  if ( (seatfile = open("seatfile.txt", O_RDWR)) == -1 )
    perror("Error opening seatfile.txt");

  while (1) {

    if ( (err = read(seatfile, &n_flights, sizeof(n_flights))) == -1 )
      perror("Error reading seatfile.txt");
    else if (err == 0)
      break;

    if ( flight_id != n_flights ) {
      // "jump" over divider, n_seats, cr and continue.
      lseek(seatfile, sizeof(divider) + sizeof(n_seats) + sizeof(cr), SEEK_CUR);
      continue;
    }
    else {
      // "jump" over divider
      lseek(seatfile, sizeof(divider), SEEK_CUR);
      // Lock the section of the file holding n_seats
      lockf(seatfile, F_LOCK, sizeof(n_seats));
      // Read n_seats
      if ( (err = read(seatfile, &n_seats, sizeof(n_seats))) == -1 )
        perror("Error reading seatfile.txt");
      // Sleep one second after read and before write as the exercise wishes for
      sleep(1);
      // Decrement n_seats
      n_seats -= 1;
      // "Jump" back to the position where we need to write the new value to
      lseek(seatfile, -sizeof(n_seats), SEEK_CUR);
      // Write new value
      if ( (err = write(seatfile, &n_seats, sizeof(n_seats))) == -1 )
        perror("Error writing to seatfile.txt");

      // Close the file and return 0 for success
      if ( (err = close(seatfile)) == -1)
        perror("Error closing seatfile.txt");

      return 0;
    }

  }

  if ( (err = close(seatfile)) == -1 )
    perror("Error closing seatfile.txt");

  return 0;
}
