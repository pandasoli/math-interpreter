#include <stdio.h>
#include "../lang/lexer/main.c"
#include "../lang/parser/main.c"
#include "../lang/parser/nodes.c"


int main(void) {
  struct Lexer lex = newLexer("1 + 2 * 12");
  struct Parser par = newParser(&lex);

  struct Node ast = par.parse(&par);

  ast.print(&ast, "");

  return 0;
}

