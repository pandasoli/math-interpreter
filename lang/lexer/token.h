#pragma once


#ifndef LEXER_TOKEN
#define LEXER_TOKEN

enum TokenKind {
  NumTk = 0,

  PlusTk = 1,
  DashTk = 2,
  StarTk = 3,
  SlashTk = 4,
  BangTk = 5,

  OpenParenTk = 6,
  CloseParenTk = 7,

  ErrTk = 8,
  EOFTk = 9
};

struct Token {
  enum TokenKind kind;
  char *val;
  int pos;
  int len;

  void (*print)(const struct Token *);
  char *(*str_kind)(const struct Token *);
  int (*getBinOpPrece)(const struct Token *);
  int (*getPrefixUnaryOpPrece)(const struct Token *);
  int (*getPostfixUnaryOpPrece)(const struct Token *);
};

#endif

struct Token newToken(enum TokenKind, char *, int, int);

