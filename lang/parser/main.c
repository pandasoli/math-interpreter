#include <stdio.h>
#include <stdbool.h>
#include "../lexer/main.c"
#include "./nodes.c"


#ifndef PARSER
#define PARSER

struct Parser {
  struct Lexer *lex;
  struct Err *err;
  struct Token current;

  struct Node (*parse)(struct Parser *);

  struct Token *(*next)(struct Parser *);

  struct Node (*expr)(struct Parser *, int);
  struct Node (*factor)(struct Parser *);
};

struct Node Parser_parse(struct Parser *par) {
  par->next(par);
  return par->expr(par, 0);
}

struct Token *Parser_next(struct Parser *par) {
  par->current = par->lex->lex(par->lex);
  return &par->current;
}

struct Node Parser_expr(struct Parser *self, int parentPrece) {
  struct Node left = self->factor(self);
  if (left.kind == 'e') return left;

  while (true) {
    int prece = self->current.getBinOpPrece(&self->current);

    if (prece == 0 || prece <= parentPrece)
      break;

    struct Token op = self->current;

    self->next(self);
    if (self->current.kind == ErrTk) {
      struct Node nd = newNode('e', self->current.pos, self->current.len);
      nd.err = self->current.val;
      return nd;
    }

    struct Node right = self->expr(self, prece);
    if (right.kind == 'e') return newNode('e', 0, 0);

    left.left = left.make_ref(&left);
    left.kind = 'b';
    left.op = op;
    left.right = right.make_ref(&right);
    left.len = (right.pos + right.len) - left.pos;
  }

  return left;
}

struct Node Parser_factor(struct Parser *self) {
  if (self->current.kind == NumTk) {
    struct Node nd = newNode(
      'n',
      self->current.pos,
      self->current.len
    );

    nd.val = self->current;

    self->next(self);
    if (self->current.kind == ErrTk) {
      nd = newNode('e', self->current.pos, self->current.len);
      nd.err = self->current.val;
    }

    return nd;
  }

  if (self->current.kind == ErrTk) {
    struct Node nd = newNode('e', self->current.pos, self->current.len);
    nd.err = self->current.val;

    return nd;
  }

  struct Node nd = newNode('e', self->current.pos, self->current.len);

  strcpy(nd.err, "Parser_factor: ");
  strcat(nd.err, self->current.str_kind(&self->current));
  strcat(nd.err, " kind not accepted");

  strcpy(
    nd.err,
    self->err->throw(
      self->err,
      nd.err,
      self->current.pos,
      self->current.len
    )
  );

  return nd;
}


struct Parser newParser(struct Lexer *lex, struct Err *err) {
  struct Parser res;

  res.lex = lex;
  res.err = err;
  res.parse = &Parser_parse;
  res.next = &Parser_next;
  res.expr = &Parser_expr;
  res.factor = &Parser_factor;

  return res;
}

#endif

