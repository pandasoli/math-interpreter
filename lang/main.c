#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "./lexer/main.h"
#include "./lexer/token.h"
#include "./parser/main.h"
#include "./eval/main.h"
#include "./error.h"
#include "./main.h"


struct Eval_val MathInterpreter(char *text, bool print) {
  struct Error err = newError();
  struct Lexer lex = newLexer(text, &err);
  struct Parser par = newParser(&lex, &err);
  struct Eval eval = newEval(&par, &err);

  struct Eval_val res = eval.eval(&eval);

  if (print) {
    if (res.kind == 'e') printf("%s\n", res.err);
    else printf("< %f\n", res.val);
  }

  return res;
}

