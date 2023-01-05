#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./token.h"


char *Token_str_kind(const struct Token *self) {
  switch (self->kind) {
    case NumTk: return "Num"; break;

    case PlusTk : return "Plus" ; break;
    case DashTk : return "Dash" ; break;
    case StarTk : return "Star" ; break;
    case SlashTk: return "Slash"; break;
    case BangTk : return "Bang" ; break;

    case OpenParenTk : return "OpenParen" ; break;
    case CloseParenTk: return "CloseParen"; break;

    case ErrTk: return "Err"; break;
    case EOFTk: return "EOF"; break;
  }
}

void Token_print(const struct Token *self) {
  char *kind = self->str_kind(self);

  printf(
    "Token:%s { val: '%s', pos: %d, len: %d }\n",
    kind,
    self->val,
    self->pos,
    self->len
  );
}

int Token_getPrefixUnaryOpPrece(const struct Token *self) {
  switch (self->kind) {
    case PlusTk:
    case DashTk:
      return 4;

    default:
      return 0;
  }
}

int Token_getPostfixUnaryOpPrece(const struct Token *self) {
  switch (self->kind) {
    case BangTk:
      return 3;

    default:
      return 0;
  }
}

int Token_getBinOpPrece(const struct Token *self) {
  switch (self->kind) {
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
  res.str_kind = &Token_str_kind;
  res.getPrefixUnaryOpPrece = &Token_getPrefixUnaryOpPrece;
  res.getPostfixUnaryOpPrece = &Token_getPostfixUnaryOpPrece;
  res.getBinOpPrece = &Token_getBinOpPrece;

  return res;
}

