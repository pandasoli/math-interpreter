#include <stdio.h>
#include "../lang/lexer/main.h"
#include "../lang/lexer/token.h"
#include "../lang/error.h"


int main(void) {
  struct Error err = newError();
  struct Lexer lex = newLexer("1 + 2 * 12", &err);
  struct Token token = newToken(PlusTk, "+", 0, 1);

  do {
    token = lex.lex(&lex);
    token.print(&token);
  }
  while (token.kind != ErrTk && token.kind != EOFTk);

  return 0;
}

