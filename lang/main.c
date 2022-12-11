#include <string.h>
#include "./lexer/main.c"


void run(char *text) {
  struct Lexer lex = newLexer(text);
  struct Token tk;

  while (tk.kind != EOFTk) {
    tk = lex.lex(&lex);
    tk.print(&tk);
  }
}

