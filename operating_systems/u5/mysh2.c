#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

#define MAX          1024
#define READ         0
#define WRITE        1

#define NUM_OF_PIPES 2

#define PARENT       1
#define CHILD        0

// Erstelle zwei Pipes zur bidirektionalen Kommunikation zwischen
// Eltern- und Kindprozess.

int pipes            [NUM_OF_PIPES][NUM_OF_PIPES];

// Deklariere die Pipes. 0 definiert Lesen und 1 das Schreiben.

#define PARENT_READ  (pipes[PARENT][READ])
#define PARENT_WRITE    (pipes[CHILD][WRITE])

#define CHILD_READ      (pipes[CHILD][READ])
#define CHILD_WRITE     (pipes[PARENT][WRITE]) // wait


// Funktion, ohne Rückgabewert, zur Ausführung eines Befehls,
// das mittels Aufruf übergeben wurde.
void parser(char *cmd){

   pid_t pid;
   int status;

   // Pipe für Eltern und Kind
   pipe(pipes[PARENT]);
   pipe(pipes[CHILD]);

   if( (pid = fork()) == 0){

      // Dupliziere alten File Descriptor auf neuen FD.
      dup2(CHILD_READ, STDIN_FILENO);
      dup2(CHILD_WRITE, STDOUT_FILENO);

      // Nicht benutzte Pipes werden geschlossen.
      close(CHILD_WRITE);
      close(PARENT_READ);
      close(PARENT_WRITE);

      // Auslesen des Befehls aus dem Pipe und ausführen mit execlp
      char buffer[MAX];
      int out = read(CHILD_READ, buffer, sizeof(buffer)-1);
      execlp(buffer, buffer, NULL);

   } else if(pid > 0) {
      // Nicht benutzte Pipes werden geschlossen.
      close(CHILD_READ);
      close(CHILD_WRITE);
      // Elternprozess schreibt Befehl für Kind in die Pipe.
      write(PARENT_WRITE, cmd, 20);
      // Wartet auf die Terminierung vom Kindprozess.
      waitpid(pid, &status, 0);

      // Lese Ausgabe aus der Pipe, das vom Kind geschrieben wurde.
      char readBuffer[MAX];
      int out = read(PARENT_READ, readBuffer, sizeof(readBuffer)-1);
        if (out >= 0) {
            readBuffer[out] = 0;
            printf("%s", readBuffer);
        } else {
            printf("IO Error\n");
        }
   }
}

int main(){

	// Endlos-Schleife mit Befehlabfrage
   while(1){
      char command[16];
      printf("%s@%s$ ", getenv("USER"),getenv("TERM"));
      scanf("%s", command);
      parser(command);
   }

   return 0;
}

