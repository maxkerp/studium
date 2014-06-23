#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(void) {

  void *handle;
  int (*globalFunc)(void);
  char *error;

  typedef void (* privateFuncPtr)();
  typedef privateFuncPtr (* privateFunctionPointer)();

  //Öffnen der Library
  handle = dlopen ("/Users/hkernbach/FH/BS/uebung17/mylib.so", RTLD_LAZY);

  if (!handle) {
  //Falls handle nicht vorhanden, brich ab
    fputs (dlerror(), stderr);
    exit(1);
  }

  //Benutzen einer lokalen Funtion d. Library
  privateFunctionPointer privHelper = (privateFunctionPointer) dlsym(handle, "privateHelper");
  privateFuncPtr localFunc = privHelper();

  //Benutzen einer globalen Funktion d. Library
  globalFunc = dlsym(handle, "publicFunction");

  if ((error = dlerror()) != NULL)  {
  //Beende falls Fehler vorgekommen ist
    fputs(error, stderr);
    exit(1);
  }

  //Gebe Ergebnis der Funktion aus
  localFunc();
  globalFunc();
  //Beende das Binden der dyn. Library
  dlclose(handle);

  //Beende die Funktion
  return 0;
}
