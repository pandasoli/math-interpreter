#include <stdio.h>
#include "./lang/main.c"


int main(void) {
  char* code = "1 + 2 * 12";
  run(code);

  return 0;
}

