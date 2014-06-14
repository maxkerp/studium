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

//==============================================================================
// dummy function
void
dummy_func (const char *string)
{
  printf(string);
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
    case 'c': dummy_func("in create\n");
              break;
    case 'l': dummy_func("in list\n");
              break;
    case 's': dummy_func("in sell\n");
              break;
    default:  fprintf(stderr, "Usage: %s [-c flights seats] [-l] [-s flight]\n",
                  argv[0]);
              exit(EXIT_FAILURE);
    }
  }

  exit(EXIT_SUCCESS);
}

