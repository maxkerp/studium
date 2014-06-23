#include <stdio.h>

void publicFunction(void) {
  puts("Hello, I'm a public function");
}

static void privateFunction (void) {
  puts("Hello, I'm a private function");
}

typedef void (* privateFunctionPointer)();

privateFunctionPointer privateHelper() {
  return &privateFunction;
}
