#include <string.h>
#include "./lexer/main.c"
#include "./lexer/tokens.c"
#include "./parser/main.c"
#include "../error.c"


void run(char *text) {
  struct Err err = newErr();
  struct Lexer lex = newLexer(text, &err);
  struct Parser par = newParser(&lex, &err);

  struct Node ast = par.parse(&par);
  ast.print(&ast, "");
}

