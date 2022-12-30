#include <string.h>
#include "./lexer/main.c"
#include "./lexer/tokens.c"
#include "./parser/main.c"
#include "./eval/main.c"
#include "../error.c"


void run(char *text) {
  struct Err err = newErr();
  struct Lexer lex = newLexer(text, &err);
  struct Parser par = newParser(&lex, &err);
  struct Eval eval = newEval(&par, &err);

  struct Eval_val res = eval.eval(&eval);

  if (res.kind == 'e') printf("%s\n", res.err);
  else printf("< %f\n", res.val);
}

