############################################################
## Name: Heiko Kernbach									  ##
## Matrikelnummer: 9019307								  ##
## Gruppe: 5											  ##
## Erstellungsdatum: 31.03.2014						      ##
## Funktionsumfang: Laden und Benutzen einer dyn. Library ##
############################################################

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

int main(void) {

  void *handle;
  double (*round)(double);
  char *error;

  //Öffnen der Library libm.dylib
  handle = dlopen ("/usr/lib/libm.dylib", RTLD_LAZY);
  if (!handle) {
	//Falls handle nicht vorhanden, brich ab
    fputs (dlerror(), stderr);
    exit(1);
  }

  //Wechsle das Verzeichnis
  chdir("/Users/hkernbach/FH/BS/chrootdir");
  if (chroot("/Users/hkernbach/FH/BS/chrootdir") != 0) {
	//Falls Fehler vorhanden, beende das Programm
    perror("chrootdir error");
    return 1;
  }

  //Benutzen einer Funktion aus der Library
  round = dlsym(handle, "round");
  if ((error = dlerror()) != NULL)  {
	//Beende falls Fehler vorgekommen ist
    fputs(error, stderr);
    exit(1);
  }
  
  //Gebe Ergebnis der Funktion aus
  printf ("%f\n", round(2.3));
  //Beende das Binden der dyn. Library
  dlclose(handle);

  //Beende die Funktion
  return 0;
}
