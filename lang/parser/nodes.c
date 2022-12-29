#include <stdlib.h>
#include "../lexer/tokens.c"

#ifndef PARSER_NODES
#define PARSER_NODES 1

struct Node {
  /*
    n - NumLit
    b - BinNode
    u - UnaryNode
  */
  char kind;

  struct Node *left;
  struct Token op;
  struct Node *right;
  struct Token val;

  int pos;
  int len;

  void (*print)(const struct Node *, char *);
  struct Node *(*make_ref)(const struct Node *);
};


void Node_print(const struct Node *node, char *last_indent) {
  char indent[255] = "";
  strcat(indent, last_indent);

  switch (node->kind) {
    case 'n':
      node->val.print(&node->val);
      break;
    case 'u':
      printf("%sUnary:\n", indent);
      strcat(indent, "  ");

      printf("%s", indent);
      node->op.print(&node->op);

      printf("%s", indent);
      node->right->print(node->right, indent);
      break;
    case 'b':
      printf("%sBinary:\n", indent);
      strcat(indent, "  ");

      printf("%s", indent);
      node->left->print(node->left, indent);

      printf("%s", indent);
      node->op.print(&node->op);

      printf("%s", indent);
      node->right->print(node->right, indent);
      break;
  }
}

struct Node *Node_make_ref(const struct Node *node) {
  struct Node *res =
    (struct Node *) malloc(sizeof(struct Node));

  res->kind = node->kind;
  res->pos = node->pos;
  res->len = node->len;
  res->print = node->print;
  res->make_ref = node->make_ref;

  switch (node->kind) {
    case 'u':
      res->right = node->right;
      break;
    case 'b':
      res->left = node->left;
      res->right = node->right;
      break;
  }

  return res;
}

struct Node newNode(char kind, int pos, int len) {
  struct Node res;

  res.kind = kind;
  res.pos = pos;
  res.len = len;
  res.print = &Node_print;
  res.make_ref = &Node_make_ref;

  switch (kind) {
    case 'u':
      res.right = (struct Node *) malloc(sizeof(struct Node));
      break;
    case 'b':
      res.left = (struct Node *) malloc(sizeof(struct Node));
      res.right = (struct Node *) malloc(sizeof(struct Node));
      break;
  }

  return res;
}

#endif

