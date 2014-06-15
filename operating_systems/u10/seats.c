/*******************************************************************************
 * Author:  Maximilain Kerp
 * Group:   5
 * Date:    June 14th, 2014
 * Pirpose: This program shows the use of lseek() and
 *          flock(). It is very simple to use.
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

#include <stdio.h>     // fopen(), perror()
#include <stdlib.h>      // exit(), EXIT_SUCCESS
#include <unistd.h>    // write(), read(), lseek(), lockf(),
                       // sleep(), getopt()
#include <sys/types.h> // lseek()
#include <fcntl.h>     // for FLAGS O_WRONLY in open(
#include <string.h>    // strlen()

//==============================================================================
// dummy function
void
dummy_func (const char *string)
{
  printf(string);
}

//==============================================================================
// function which creates the seatfile.txt file
int
create_seats (int num_flights, int num_seats)
{
  printf("Creating %d data sets with an initial number of %d seats...\n",
      num_flights, num_seats);

  char *buf = "This is a test\n";
  int seatfile = open("./seatfile.txt", O_WRONLY | O_CREAT, S_IRWXU);
  for (int i = 0; i < num_flights; i++){
    write(seatfile, buf, strlen(buf));
  }
  close(seatfile);
  return 0;
}

//==============================================================================
// function to list all seats
int
list_seats(void)
{

  return 0;
}

//==============================================================================
// function selling a seat
int
sell_seat (int flight_id)
{
  printf("Selling 1 seat on flight %d\n", flight_id);
  return 0;
}
//==============================================================================
// MAIN
int
main (int argc, char **argv)
{
  int ch;
  opterr = 0;

  while ( (ch = getopt(argc, argv, "c:s:l")) != EOF )
  {
    switch (ch) {
    case 'c': create_seats(atoi(argv[optind - 1]), atoi(argv[optind]));
              break;
    case 'l': dummy_func("in list\n");
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

