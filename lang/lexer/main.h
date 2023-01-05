#pragma once
#include "../error.h"


#ifndef LEXER
#define LEXER

struct Lexer {
  char *text;
  int counter;
  char current;
  struct Error *err;

  struct Token (*lex)(struct Lexer *);

  char *(*next)(struct Lexer *);
  char *(*back)(struct Lexer *);

  struct Token (*num)(struct Lexer *, char *, const int, int *);
};

#endif

struct Lexer newLexer(const char *, struct Error *);

