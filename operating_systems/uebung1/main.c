#include <sys/types.h> // for process id pid_t / pid
#include <unistd.h>  // system api fork, write, read
#include <stdio.h>  // printf
#include <stdlib.h> // exit(0) include

int glob = 6;
char buf[] = "a write to stdout\n";

int main(void) {

  int   var;
  pid_t pid;
  var = 88;

  //STDOUT_FILENO Symbolische Konstante file descriptor number 0 Eingabe, 1 Schreiben, 2 Fehler

  if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
    //write gibt zurück wieviele Zeichen geschrieben werden konnten
    perror("write error");
  printf("before fork\n");
  //fflush(stdout);

  if ( (pid = fork()) < 0)
    //Nach dem Fork zwei Prozesse mit dem selben Quelltext
    //Scheduler regelt die Priorität im Ablauf beider Prozesse
    //Falls pid < 0 (z.B. -1) dann ist hier beim Kindprozess etwas schief gegangen
    perror("fork error");
  else if (pid == 0) {
    //Wartet zwei Prozessintervalle, anschließend gibt jeder Prozess das untere printf aus
    glob++;
    var++;
  }
  else
    sleep(2);
    printf("pid = %d, glob =%d, var = %d\n", getpid(), glob, var);
    //getpid() = bekomme eigene pid (auch kindprozess usw);
    //getppid() = bekomme prozess id (pid) des vaterprozesses
    exit(0);
}
