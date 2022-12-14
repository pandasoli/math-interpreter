#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "../lexer/main.h"
#include "./node.h"
#include "../error.h"
#include "./main.h"


struct Node Parser_parse(struct Parser *par) {
  par->next(par);
  return par->expr(par, 0);
}

struct Token *Parser_next(struct Parser *par) {
  par->current = par->lex->lex(par->lex);
  return &par->current;
}

struct Node Parser_expr(struct Parser *self, int parentPrece) {
  struct Node left;
  int unaryOpPrece = self->current.getPrefixUnaryOpPrece(&self->current);

  if (unaryOpPrece != 0 && unaryOpPrece >= parentPrece) {
    struct Token op = self->current;
    self->next(self);

    struct Node operand = self->expr(self, unaryOpPrece);
    if (operand.kind == 'e') return left;

    left = newNode(
      'u',
      op.pos,
      (operand.pos + operand.len) - op.pos
    );

    left.op = op;
    left.right = operand.make_ref(&operand);
  }
  else {
    left = self->factor(self);
    if (left.kind == 'e') return left;
  }

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
    if (right.kind == 'e') return right;

    left.left = left.make_ref(&left);
    left.kind = 'b';
    left.op = op;
    left.right = right.make_ref(&right);
    left.len = (right.pos + right.len) - left.pos;
  }

  return left;
}

struct Node Parser_factor(struct Parser *self) {
  struct Node node;

  switch (self->current.kind) {
    case NumTk: {
      node = newNode(
        'n',
        self->current.pos,
        self->current.len
      );

      node.val = self->current;

      self->next(self);
      if (self->current.kind == ErrTk) {
        node = newNode('e', self->current.pos, self->current.len);
        node.err = self->current.val;
      }

      break;
    }

    case OpenParenTk: {
      self->next(self);
      node = self->expr(self, 0);

      if (self->current.kind != CloseParenTk) {
        struct Node node = newNode('e', self->current.pos, self->current.len);
        strcpy(node.err, "Expected \")\", found \"");
        strcat(node.err, self->current.val);
        strcat(node.err, "\"");

        strcpy(
          node.err,
          self->err->throw_(
            self->err,
            node.err,
            self->current.pos,
            self->current.len
          )
        );

        return node;
      }
      self->next(self);

      break;
    }

    case ErrTk: {
      struct Node node = newNode('e', self->current.pos, self->current.len);
      node.err = self->current.val;

      return node;
    }

    default: {
      struct Node node = newNode('e', self->current.pos, self->current.len);

      strcpy(node.err, "Parser_factor: expected number or (, found ");
      strcat(node.err, self->current.str_kind(&self->current));

      strcpy(
        node.err,
        self->err->throw_(
          self->err,
          node.err,
          self->current.pos,
          self->current.len
        )
      );

      return node;
    }
  }

  int unaryOpPrece = self->current.getPostfixUnaryOpPrece(&self->current);

  if (unaryOpPrece > 0) {
    struct Token op = self->current;

    struct Node expr = newNode('u', node.pos, (op.pos + op.len) - node.pos);
    expr.op = op;
    expr.right = node.make_ref(&node);

    self->next(self);

    return expr;
  }

  return node;
}


struct Parser newParser(struct Lexer *lex, struct Error *err) {
  struct Parser res;

  res.lex = lex;
  res.err = err;
  res.parse = &Parser_parse;
  res.next = &Parser_next;
  res.expr = &Parser_expr;
  res.factor = &Parser_factor;

  return res;
}

