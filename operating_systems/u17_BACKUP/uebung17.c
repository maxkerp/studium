#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

int main(void) {

  void *handle;
  int (*globalFunc)(void);
  //int (*localFunc)(void);
  char *error;

  //Öffnen der Library
  handle = dlopen ("/Users/hkernbach/FH/BS/uebung17/libfoo.so", RTLD_LAZY);
  if (!handle) {
  //Falls handle nicht vorhanden, brich ab
    fputs (dlerror(), stderr);
    exit(1);
  }

  //Benutzen einer Funktion aus der Library
  globalFunc = dlsym(handle, "foo");
  //localFunc = dlsym(handle, "foo2");
  if ((error = dlerror()) != NULL)  {
  //Beende falls Fehler vorgekommen ist
    fputs(error, stderr);
    exit(1);
  }

  //Gebe Ergebnis der Funktion aus
  globalFunc();
//  localFunc();
  //Beende das Binden der dyn. Library
  dlclose(handle);

  //Beende die Funktion
  return 0;
}
