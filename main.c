#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "./lang/main.h"


int main(int argc, char **argv) {
  char code[255];

  if (argc > 1) {
    if (strcmp(argv[1], "test")) {
      strcpy(code, "1 + 2 * 12");
      MathInterpreter(code, true);
    }
    else
      printf("What the fuck you meant with \"%s\"?", argv[1]);
  }
  else {
    while (true) {
      printf("> ");

      fgets(code, sizeof(code), stdin);
      sscanf(code, "%[^\n]s", code);

      if (strcmp(code, "\n") == 0) break;

      MathInterpreter(code, true);
    }
  }

  return 0;
}

