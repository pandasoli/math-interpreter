#include <string.h>
#include "./lexer/main.c"


void run(char *text) {
  struct Lexer lex = newLexer(text);
  struct Token tk;

  do {
    tk = lex.lex(&lex);
    tk.print(&tk);
  }
  while (tk.kind != EOFTk && tk.kind != ErrTk);
}

