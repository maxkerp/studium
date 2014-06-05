#include <stdio.h>   // exit(0) included
#include <stdlib.h>  // printf
#include <pthread.h> // for POSIX threads

//global float mutex array. this array has the same length as account_balances array.
//every position stands for a real account balance value. when i am writing to an
//account I will set the index number to 1 => account is locked. To unlock the account
//i will set the index back to 0 => account is unlocked.
int account_mutex[10];

//global float array
float account_balances[10];

//struct for my pthreads including two integers (from, to) and a float (amount)
typedef struct pthread_data_type {
  int from;         //from index
  int to;           //to index
  float amount;     //amount to transfer
} pthread_data;

int process_transfer (int from_acct, int to_acct, float amount) {

  //check if from account or to account is already in use
  while (account_mutex[from_acct] == 1 || account_mutex[to_acct] == 1) {
    //just wait until both accounts are unlocked
  }

  printf("Starting transfer, accounts are not locked:\n");
  //now lock accounts for personal use
  account_mutex[from_acct] = 1;
  account_mutex[to_acct] =  1;

  //transfer the amount
  printf("Transfering from: %d to: %d with amount: %f\n", from_acct, to_acct, amount);
  account_balances[from_acct] -= amount;
  account_balances[to_acct] += amount;

  //now unlock accounts for other threads
  account_mutex[from_acct] = 0;
  account_mutex[to_acct] =  0;

  printf("Finished transfer.\n\n");
}

// simple function to fill data into account_balances float array
void create_balances_data () {
  for (int i = 0; i < 10; i++) {
    account_balances[i] = i;
  }
}

//simple print function, which iterates through the array and prints every value of
//it including index position
void print_balances_data () {
  printf("\n------------------------------------------\n");
  printf("Printing Balances Data: \n");
  for (int i = 0; i < 10; i++) {
    printf("Value: %f at array index position: %d\n", account_balances[i], i);
  }
  printf("------------------------------------------\n\n");
}

void pthread_starter(void *parameters) {
  pthread_data *data;                    //placeholder for data
  data = (pthread_data *) parameters;    //get data from void pointer

  //now start processing the account balance transfers
  process_transfer (data->from, data->to, data->amount);
}

int main (int argc, char **argv) {

  pthread_t thread1, thread2;    //pthread placeholder for first and second thread
  pthread_data data1, data2;     //pthread data struct for first and second thread

  //prepare data for the first account transfer
  data1.from = 1;
  data1.to = 2;
  data1.amount = 4.5;

  //prepare data for the second account transfer
  data2.from = 2;
  data2.to = 3;
  data2.amount = 2.2;

  //create data for my float account balance array
  create_balances_data();
  printf("\nData before amount transfer:\n");
  //print balance account data before any account transfers
  print_balances_data();

  //create both threads
  pthread_create(&thread1, NULL, (void *) &pthread_starter, (void *) &data1);
  pthread_create(&thread2, NULL, (void *) &pthread_starter, (void *) &data2);

  //wait for both threads to finisih
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  //now print balance account data after account tranfers finished
  printf("\nData after amount transfer:\n");
  print_balances_data();

  exit(1);
}
