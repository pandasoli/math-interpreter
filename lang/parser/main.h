#pragma once
#include "./node.h"
#include "../error.h"


#ifndef PARSER
#define PARSER

struct Parser {
  struct Lexer *lex;
  struct Error *err;
  struct Token current;

  struct Node (*parse)(struct Parser *);

  struct Token *(*next)(struct Parser *);

  struct Node (*expr)(struct Parser *, int);
  struct Node (*factor)(struct Parser *);
};

#endif

struct Parser newParser(struct Lexer *, struct Error *);

