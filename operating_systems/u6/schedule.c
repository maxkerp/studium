/*********************************************************************
 * Author   : Maximilan Kerp
 * Group    : 7
 * Date     : 19.04.14
 * Purpose  : This program is a very abstract implementation
 *            of four scheduling algorithyms. Algorithyms
 *            implemented are, first-come-first-served, preemptive-
 *            shortest-job-first, shortest-job-first, and round-robin
 *
 *********************************************************************/
#include <stdio.h>
#include <unistd.h>

//======================================================
// a process struct to mock a process
typedef struct
{
  int id;                   // the id of the process
  int burst_time;           // time needed to finish
  int arrival_time;          // time arrived in the "process-queue"
  int turnaround_time;      // waiting time

} process_t;

//=======================================================
// all methods needed for this program.
void first_come_first_serve(process_t list[]);
void shortest_job_first(process_t list[]);
void preemptive_shortest_job_first(process_t list[]);
void round_robin(process_t list[]);


//=======================================================
// MAIN
int main(int argc, char **argv)
{
  // create a static list of processes
  process_t p1 = {.id=1, .burst_time=10, .arrival_time=0};
  process_t p2 = {.id=2, .burst_time=2, .arrival_time=5};
  process_t p3 = {.id=3, .burst_time=48, .arrival_time=10};
  process_t p4 = {.id=4, .burst_time=13, .arrival_time=23};
  process_t p5 = {.id=5, .burst_time=100, .arrival_time=66};

  // in a real list we would just append the next process, this
  // is why we create an already sorted array
  process_t process_list[] = {p1, p2, p3, p4, p5};

  // call all algorithyms on the array of processes
  first_come_first_serve(process_list);
  //shortest_job_first(process_list);
  //preemptive_shortest_job_first(process_list);
  //round_robin(process_list);

  return 0;
}

//=========================================================
// FSFS
// we can ignore the arival time cause all processes
// are executed as they appear in the "list"
void first_come_first_serve(process_t list[])
{
  // starting at 0 time units
  int time = 0;
  int total_time = 0;
  // initialize time with the sum of all burst_times;
  int array_size = 5;
  for(int i = 0; i < array_size; i++)
  {
    total_time = total_time + list[i].burst_time;
    printf("Burst_time of %d is %d\n", i+1, list[i].burst_time);
  }

  printf("total_time: %d \n", total_time);
  int active_process = 0;
  do{

    // set turnaround_time if not present
    if(!list[active_process].turnaround_time){
      list[active_process].turnaround_time = time - list[active_process].arrival_time;
    }

    //  get active process and decrement burst_time
    list[active_process].burst_time--;

    // if process finished print the status and go to next one
    if(list[active_process].burst_time == 0){
      printf("time is %3d\tprocess %1d finished.\tturnaround_time was %3d\n",
          time, list[active_process].id, list[active_process].turnaround_time);
      active_process++;
    }

    //decrement time by one
    time++;

  } while ( time != total_time );

}

