###############################################################################
## Name: Heiko Kernbach                                                      ##
## Matrikelnummer: 9019307                                                   ##
## Gruppe: 5					                                             ##
## Erstellungsdatum: 19.05.2014                                              ##
## Funktionsumfang: CPU-Scheduling (Verschiedene Algorithmen)                ##
## Aufgabenblatt: 13                                                         ##
###############################################################################

#include <stdio.h>
#include <unistd.h>

typedef struct
{
  int id;                   // the id of the process
  int burst_time;           // time needed to finish
  int arrival_time;          // time arrived in the "process-queue"
  int turnaround_time;      // waiting time
  int done;
  int runtime;
} process_t;

void first_come_first_serve(process_t list[]);
void shortest_job_first(process_t list[]);
void round_robin(process_t list[]);
void preemptive_shortest_job_first(process_t list[]);

int array_size = 6;

int main(int argc, char **argv) {
  // create a static list of processes
  process_t p1 = {.id=0, .burst_time=12, .arrival_time=0, .done=0, .runtime=0};
  process_t p2 = {.id=1, .burst_time=4, .arrival_time=0, .done=0, .runtime=0};
  process_t p3 = {.id=2, .burst_time=7, .arrival_time=5, .done=0, .runtime=0};
  process_t p4 = {.id=3, .burst_time=48, .arrival_time=10, .done=0, .runtime=0};
  process_t p5 = {.id=4, .burst_time=13, .arrival_time=23, .done=0, .runtime=0};
  process_t p6 = {.id=5, .burst_time=100, .arrival_time=66, .done=0, .runtime=0};

  process_t process_list[] = {p1, p2, p3, p4, p5, p6};
<<<<<<< Local Changes
<<<<<<< Local Changes
  first_come_first_serve(process_list);
  //shortest_job_first(process_list);
=======
  first_come_first_serve(process_list);
  shortest_job_first(process_list);
  printf("#############\n");
>>>>>>> External Changes
=======
  //first_come_first_serve(process_list);
<<<<<<< Local Changes
  shortest_job_first(process_list);
  printf("#############\n");
>>>>>>> External Changes
=======
  //shortest_job_first(process_list);
<<<<<<< Local Changes
<<<<<<< Local Changes
<<<<<<< Local Changes
  printf("#############\n");
>>>>>>> External Changes
=======
  printf("#############\n");
>>>>>>> External Changes
=======
  printf("#############\n");
>>>>>>> External Changes
=======
  printf("#############\n");
>>>>>>> External Changes
  for (int i=0; i < array_size; i++) {
    process_list[0].done = 0;
  }
<<<<<<< Local Changes
<<<<<<< Local Changes
<<<<<<< Local Changes
<<<<<<< Local Changes
<<<<<<< Local Changes
<<<<<<< Local Changes
  //round_robin(process_list);
=======
  printf("#############\n");
=======
  printf("#############\n");
>>>>>>> External Changes
=======
  printf("#############\n");
>>>>>>> External Changes
=======
  printf("#############\n");
>>>>>>> External Changes
=======
  printf("#############\n");
>>>>>>> External Changes
  round_robin(process_list);
>>>>>>> External Changes
=======
  printf("#############\n");
  //round_robin(process_list);
>>>>>>> External Changes
  return 0;
}

int calculate_total_time(process_t list[]) {
  int total_time = 0;
  for(int i = 0; i < array_size; i++) {
    total_time = total_time + list[i].burst_time;
    //printf("Burst_time of %d is %d\n", i+1, list[i].burst_time);
  }
  return total_time;
}

//calculate shortest left runtime of a process 
<<<<<<< Local Changes
<<<<<<< Local Changes

int calculateShortestTime(process_t list[]) {
=======

int calculateShortestTime(process_t list) {
>>>>>>> External Changes
=======

int calculateShortestTime(process_t list[]) {
>>>>>>> External Changes
  int shortest = 0;
  int shortestid = 0;
  //iterate through process array
  for (int i = 0; i < array_size; i++) {
    printf("%d\n", list[i].runtime;
    int diff = list[i].burst_time - list[i].runtime;
    //if value is not set, or calculated value is smaller
    if (shortest == 0 || diff < shortest) {
      shortest = diff;
      shortestid = list[i].id;
    }
    return shortestid;
  }
}

//shortest duration of a process gains highest priority
void preemptive_shortest_job_first(process_t list[]) {
  int total_time = calculate_total_time(list);
  int time = 0;

  while(time != total_time) {
  //couldnt resolve my problem in my calculate shortest time function
  //error: subscripted value is not an array, pointer, or vector
  //but in my other functions, im using it the same way?


    //here would be my calculate shortest time function to check
    //which function needs less time to finish. after that check
    //it would run until another process may have a faster finish.
    //so every loop i have to check if another process could be faster.

    time++;
  }
}

//static work time for every process
void round_robin(process_t list[]) {
  int time_for_every_process = 10;
  int current_process = 0;
  int total_time = calculate_total_time(list);
  int time = 0;

  while (time != total_time) {
    //every 10 interval
    printf("process %d running\n", current_process);
    if (time % time_for_every_process == 0) {
      //if process is finished, dont schedule time for it
      if (list[current_process].runtime >= list[current_process].burst_time) {
        current_process++;
      }
      printf("others process turn\n");
      if (current_process < array_size-1) {
        current_process++;
      }
      else {
        current_process = 0;
      }
      printf("process %d running\n", current_process);
      list[current_process].runtime = list[current_process].runtime + 1;
    }
    time++;
  }
  printf("finished after %d\n ", time);
}

//shortest runtime of a job gains highest priority
void shortest_job_first(process_t list[]) {
  //funktioniert leider nicht
  int total_time = calculate_total_time(list);
  int already_done[array_size+1];


  int lowBurstTime = 0;
  int lowID = 0;


  //iterate through estimated total time
  for (int time = 0; time < total_time; time++) {
    //iterate process array for every time loop
    for (int pos = 0; pos < array_size; pos++) {
      //if element arrival time < time and element not handled
      if (list[pos].arrival_time <= time && list[pos].done == 0) {
        printf("id %d  burst time: %d\n", list[pos].id, list[pos].burst_time);

        if (lowBurstTime == 0) {
          lowBurstTime = list[pos].burst_time;
          lowID = list[pos].id;
        }
        else if (lowBurstTime > list[pos].burst_time) {
          lowBurstTime = list[pos].burst_time;
          lowID = list[pos].id;
          printf("i am smaller ( \n");
        }
      }

    }
    list[lowID].done = 1;
    lowBurstTime = 0;
    lowID = 0;
  }

}

//first service has highest priority (in order)
void first_come_first_serve(process_t list[]) {
  // starting at 0 time units
  int time = 0;
  int total_time = calculate_total_time(list);
  // initialize time with the sum of all burst_times;
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
