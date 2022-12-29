#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef LEXER_TOKENS
#define LEXER_TOKENS 1

enum TokenKind {
  NumTk = 0,

  PlusTk = 1,
  DashTk = 2,
  StarTk = 3,
  SlashTk = 4,

  ErrTk = 5,
  EOFTk = 6
};

struct Token {
  enum TokenKind kind;
  char *val;
  int pos;
  int len;

  void (*print)(const struct Token *);
  int (*getBinOpPrece)(const struct Token *);
  int (*getUnaryOpPrece)(const struct Token *);
};

void Token_print(const struct Token *token) {
  char kind[6];

  switch (token->kind) {
    case NumTk  : strcpy(kind, "Num"  ); break;
    case PlusTk : strcpy(kind, "Plus" ); break;
    case DashTk : strcpy(kind, "Dash" ); break;
    case StarTk : strcpy(kind, "Star" ); break;
    case SlashTk: strcpy(kind, "Slash"); break;
    case ErrTk  : strcpy(kind, "Err"  ); break;
    case EOFTk  : strcpy(kind, "EOF"  ); break;
  }

  printf(
    "Token:%s { val: '%s', pos: %d, len: %d }\n",
    kind,
    token->val,
    token->pos,
    token->len
  );
}

int Token_getUnaryOpPrece(const struct Token *token) {
  switch (token->kind) {
    case PlusTk:
    case DashTk:
      return 3;

    default:
      return 0;
  }
}

int Token_getBinOpPrece(const struct Token *token) {
  switch (token->kind) {
    case StarTk:
    case SlashTk:
      return 2;

    case PlusTk:
    case DashTk:
      return 1;

    default:
      return 0;
  }
}

struct Token newToken(enum TokenKind kind, char *val, int pos, int len) {
  struct Token res;

  res.kind = kind;
  res.val = (char *) malloc(sizeof(char) * 255);
  strcpy(res.val, val);
  res.pos = pos;
  res.len = len;
  res.print = &Token_print;
  res.getUnaryOpPrece = &Token_getUnaryOpPrece;
  res.getBinOpPrece = &Token_getBinOpPrece;

  return res;
}

#endif

