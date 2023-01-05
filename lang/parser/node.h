#pragma once
#include "../lexer/token.h"


#ifndef PARSER_NODE
#define PARSER_NODE

struct Node {
  /*
    n - NumLit
    b - BinNode
    u - UnaryNode
    e - Err
  */
  char kind;

  struct Node *left;
  struct Token op;
  struct Node *right;
  struct Token val;
  char *err;

  int pos;
  int len;

  void (*print)(const struct Node *, char *);
  struct Node *(*make_ref)(const struct Node *);
};

#endif

struct Node newNode(char, int, int);

