#include <stdio.h>
#include "../lang/lexer/main.h"
#include "../lang/parser/main.h"
#include "../lang/parser/node.h"
#include "../lang/error.h"


int main(void) {
  struct Error err = newError();
  struct Lexer lex = newLexer("1 + 2 * 12", &err);
  struct Parser par = newParser(&lex, &err);

  struct Node ast = par.parse(&par);

  ast.print(&ast, "");

  return 0;
}

