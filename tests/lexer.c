#include <stdio.h>
#include "../lang/lexer/main.c"
#include "../lang/lexer/tokens.c"


int main(void) {
  struct Lexer lex = newLexer("1 + 2 * 12");
  struct Token token = newToken(PlusTk, "+", 0, 1);

  do {
    token = lex.lex(&lex);
    token.print(&token);
  }
  while (token.kind != ErrTk && token.kind != EOFTk);

  return 0;
}

