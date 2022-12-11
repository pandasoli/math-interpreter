#include <string.h>
#include <stdio.h>


enum TokenKind {
  NumTk,

  PlusTk,
  DashTk,
  StarTk,
  SlashTk,

  ErrTk,
  EOFTk
};

struct Token {
  enum TokenKind kind;
  char *val;
  int pos;
  int len;

  void (*print)(const struct Token *);
};

void Token_print(const struct Token *token) {
  printf(
    "Token:%d(%s, %d, %d)",
    token->kind,
    token->val,
    token->pos,
    token->len
  );
}

struct Token newToken(enum TokenKind kind, char *val, int pos, int len) {
  struct Token res;

  res.kind = kind;
  strcpy(res.val, val);
  res.pos = pos;
  res.len = len;
  res.print = &Token_print;

  return res;
}

