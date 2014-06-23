#include <stdio.h>
#include "foo.h"

int main(void) {
  puts("This is a shared library test...");
  foo();
  foo2();
  return 0;
}
