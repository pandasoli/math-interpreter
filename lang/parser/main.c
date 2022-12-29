#include <stdio.h>
#include <stdbool.h>
#include "../lexer/main.c"
#include "./nodes.c"


#ifndef PARSER
#define PARSER 1

struct Parser {
  struct Lexer *lex;
  struct Token current;
  int return_type;

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

struct Node Parser_expr(struct Parser *par, int parentPrece) {
  struct Node left = par->factor(par);

  while (true) {
    int prece = par->current.getBinOpPrece(&par->current);

    if (prece == 0 || prece <= parentPrece)
      break;

    struct Token op = par->current;
    par->next(par);
    struct Node right = par->expr(par, prece);

    left.left = left.make_ref(&left);
    left.kind = 'b';
    left.op = op;
    left.right = right.make_ref(&right);
    left.len = (right.pos + right.len) - left.pos;
  }

  return left;
}

struct Node Parser_factor(struct Parser *par) {
  if (par->current.kind == NumTk) {
    struct Node nd = newNode(
      'n',
      par->current.pos,
      par->current.len
    );

    nd.val = par->current;
    par->next(par);

    return nd;
  }

  printf("Parser_factor: %d kind not accepted\n", par->current.kind);
  abort();
}


struct Parser newParser(struct Lexer *lex) {
  struct Parser res;

  res.lex = lex;
  res.parse = &Parser_parse;
  res.next = &Parser_next;
  res.expr = &Parser_expr;
  res.factor = &Parser_factor;

  return res;
}

#endif

