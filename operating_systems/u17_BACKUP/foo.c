#include <stdio.h>

void foo(void) {
  puts("Hello, I'm a public function");
}

static void foo2(void) {
  puts("Hello, I'm a local function");
}
