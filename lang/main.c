#include <string.h>
#include "./lexer/main.c"
#include "./lexer/tokens.c"
#include "./parser/main.c"


void run(char *text) {
  struct Lexer lex = newLexer(text);
  struct Parser par = newParser(&lex);

  struct Node ast = par.parse(&par);
  ast.print(&ast, "");
}

