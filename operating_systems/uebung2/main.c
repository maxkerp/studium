#include <stdio.h> //exit(0) included
#include <stdlib.h>  // printf
#include <string.h> // string functions
#include <sys/types.h> // for process id pid_t / pid
#include <unistd.h>  // system api fork, write, read

int main () {
  int bytes_read; // buffer
  int nbytes = 100; //Größe für lesebuffer
  char *my_string; // string pointer
  int returnStatus;  // child return status
  pid_t pid;  // variable für pid

  // Befehle die zur Laufzeit akzeptiert werden
  char *command1 = "date";
  char *command2 = "who";
  char *command3 = "tty";
  char *command4 = "ps";
  char *command5 = "ls";
  char *command6 = "exit";

  //allokiere Speicher für my_string variable
  my_string = (char *) malloc (nbytes + 1);

  //Endlosschleife
  while (1) {
    printf("Geben Sie einen Befehl ein:\n");
    bytes_read = getline (&my_string, &nbytes, stdin);
    printf("Eingabe: ");
    printf(my_string);

    // falls my_string geschrieben wurde, entferne Umbruch
    if (my_string != NULL) {
      size_t last = strlen (my_string) - 1;
      if (my_string[last] == '\n') {
        //ersetze mit gültigem Ende für einen String
        my_string[last] = '\0';
      }
    }

    if (bytes_read == -1) {
      // Fehler beim lesen, beende Programm
      printf("Error!");
      exit(0);
    }

    if (strcmp(command1, my_string) == 0) {
      if ((pid = fork()) < 0) {
        //Melde fork Fehler
        perror("fork error");
      }
      else if (pid == 0) {
        // date = aufzurufendes Programm
        // NULL = terminiere im Anschluss
        execlp ("date", "date", NULL);
      }
      printf("\n");
    }
    else if (strcmp(command2, my_string) == 0) {
      if ((pid = fork()) < 0) {
        perror("fork error");
      }
      else if (pid == 0) {
        execlp ("who", "who", NULL);
      }
      printf("\n");
    }
    else if (strcmp(command3, my_string) == 0) {
      if ((pid = fork()) < 0) {
        perror("fork error");
      }
      else if (pid == 0) {
        execlp ("tty", "tty", NULL);
      }
      printf("\n");
    }
    else if (strcmp(command4, my_string) == 0) {
      if ((pid = fork()) < 0) {
        perror("fork error");
      }
      else if (pid == 0) {
        execlp ("ps", "ps", NULL);
      }
      printf("\n");
    }
    else if (strcmp(command5, my_string) == 0) {
      if ((pid = fork()) < 0) {
        perror("fork error");
      }
      else if (pid == 0) {
        execlp ("ls", "ls", NULL);
      }
      printf("\n");
    }
    else if (strcmp(command6, my_string) == 0) {
      printf("Programm Ende\n");
      exit(0);
    }

    //überprüfe Ablauf des Kind-Prozesses
    waitpid(pid, &returnStatus, 0);
    if (returnStatus == 0) {
      // Keine Fehler beim Kindprozess
      printf("Kindprozess fertig\n");
    }
    else if (returnStatus == 1) {
      //Fehler beim Kindprozess
      printf("Kindprozess Error\n");
      //Beende Programm
      exit(0);
    }

  }

  exit(0);
}
