/*******************************************************************************
 * Author:    Maximilian Kerp
 * Gruop:     7
 * Date:      20.04.2013
 * Purpose:   Implementing an abstract preemptive-shortest-job-first
 *            algorithim
 *
 * Bursttime muss größer 2 gewählt werden
 * Auf Anforderungen des Programmes warten.
 ******************************************************************************/

#include <stdio.h>

//============================================================================
// Struct für Prozessinformationen
typedef struct
{
  int id;
  int arrival;
  int burst;
  int rem;
  int wait;
  int finish;
  int turnaround;
} proc_t;

//============================================================================
// GLOBALS
proc_t process[10];
int no;

//============================================================================
// MAIN
int main(int argc, char **argv)
{
  int n = 5; // Anzahl der Prozesse
  int i, j,k, time = 0; // Hilfsvariablen
  proc_t temp;
  int chkprocess(int);
  int nextprocess();

  printf("\n---PREEMPTIVE SHORTEST JOB FIRST---\n ");
  printf("\nAnzahl der Prozesse: %d",n);

  // Zuweisung für Prozesse mit Ankunfszeit und Burstzeit
  for(i = 1; i <= n; i++)
  {
    process[i].id = i;

    printf("\nGebe Ankunftszeit für Prozess %d ein: ", i);
    scanf("%d", &(process[i].arrival));

    printf("Gebe burst time > 2 für Prozess %d ein: ", i);
    scanf("%d", &(process[i].burst));

    process[i].rem = process[i].burst;

  }

  // Sortieren der Prozesse nach Ankunftszeit
  for(i = 1; i <= n; i++)
  {
    for(j = i + 1; j <= n; j++)
    {
      if(process[i].arrival > process[j].arrival)
      {
        temp = process[i];
        process[i] = process[j];
        process[j] = temp;
      }
    }
  }

 // Zuweisen der Hilfsvariablen Für Prozess Ids
  no = 0;
  j = 1;

/** Zuerst wird geprüft ob der aktuelle Prozess noch läuft.
 *
 * Im ersten If Block wird der Prozess mit der
 * Ankunftszeit mit der aktuellen Zeit verglichen
 * und falls die Zeiten identisch, wird die Prozesshilfsvariable
 * no hochgezählt, um im nächsten durchgang mit dem nächsten Prozess
 * weiterrechnen zu können.  * wurde und wenn ja, dann wird seine Finishing Time festgelegt.
 * noch den Prozess mit der kleinsten Remaining Time.
 *
 * Prozess mit der aktuell kürzesten Remaining Time noch läuft, falls ja
 * wird die Remaining Time dekrementiert und  Wartezeit der anderen Prozesse erhöht.
 *
 * Im else block wird, falls der Prozess mit der aktuell kürzesten Remaining
 * Time nicht mehr läuft, die Finishing Time dieses Prozesses festgelegt,
 * desweiteren wird die time variable dekrementiert
 * und für den letzten Prozess die Finishing Time festgelegt
 */

  while(chkprocess(n) == 1)
  {
    if(process[no + 1].arrival == time)
    {
      no++;
      if(process[j].rem==0)
        process[j].finish=time;

      j = nextprocess();
    }

    if(process[j].rem != 0)
    {
      process[j].rem--;
      for(i = 1; i <= no; i++)
      {
        if(i != j && process[i].rem != 0)
          process[i].wait++;
      }
    }
    else
    {
    process[j].finish = time;
      j=nextprocess();
      time--;
      k=j;

    }

    time++;
  }

// Zuweisung der Finishing Time des längsten Prozesses
  process[k].finish = time;


  // Übersicht der Prozesse als Tabelle
  printf("\n\n---PREEMPTIVE SHORTEST JOB FIRST---");
  printf("\n Prozess  Ankunfts  Burst   Warte  Finishing turnaround \n");
  printf("%5s %9s %7s %10s %8s %9s\n\n", "id", "zeit", "zeit", "zeit", "zeit", "zeit");


  for(i = 1; i <= n; i++)
  {
    // Berechnung der Prozess Turn Around Time
    process[i].turnaround = process[i].wait + process[i].burst;

    printf("%5d %8d %7d  %8d %10d %9d  ", process[i].id, process[i].arrival,
        process[i].burst, process[i].wait, process[i].finish,
        process[i].turnaround);

    printf("\n\n");
  }
}

// Prüft ob Prozess[i] noch aktiv
int chkprocess(int s)
{
  int i;
  for(i = 1; i <= s; i++)
  {
    if(process[i].rem != 0)
      return 1;
  }
  return 0;
}

// Prüft, ob nächster Prozess kleinere Remaining Time hat,
//wenn ja, wird dieser als neuer kürzester Prozess zugewiesen*/
int nextprocess()
{
  int min, l, i;
  min = 32000;  //Absicherung für Bursttime
  for(i = 1; i <= no; i++)
  {
    if( process[i].rem!=0 && process[i].rem < min)
    {
      min = process[i].rem;
      l = i;
    }
  }
  return l;
}
