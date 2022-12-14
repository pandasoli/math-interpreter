#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lexer/token.h"
#include "./node.h"


void Node_print(const struct Node *node, char *last_indent) {
  char indent[255] = "";
  strcat(indent, last_indent);

  switch (node->kind) {
    case 'e':
      printf("%s\n", node->err);
      break;
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
  res->right = node->right;
  res->left = node->left;
  res->op = node->op;
  res->val = node->val;
  res->err = node->err;

  return res;
}

struct Node newNode(char kind, int pos, int len) {
  struct Node res;

  res.kind = kind;
  res.pos = pos;
  res.len = len;
  res.err = malloc(0);
  res.print = &Node_print;
  res.make_ref = &Node_make_ref;

  res.left = malloc(0);
  res.op = (struct Token) {};
  res.right = malloc(0);

  switch (kind) {
    case 'e':
      res.err = (char *) malloc(sizeof(char) * 255);
      break;
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

