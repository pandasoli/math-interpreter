#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


#ifndef ERROR
#define ERROR

struct Err {
  bool err;

  char *(*throw)(struct Err *, const char *, const int, const int);
};

char *Err_throw(struct Err *self, const char *msg, const int pos, const int len) {
  self->err = true;
  char *res = calloc(pos + len + strlen(msg) + 1, sizeof(char));

  for (int i = 0; i < pos + 2; i++) strcat(res, " ");
  for (int i = 0; i < len; i++) strcat(res, "^");

  strcat(res, "\n");
  strcat(res, msg);

  return res;
}


struct Err newErr() {
  struct Err res;

  res.err = false;
  res.throw = &Err_throw;

  return res;
}

#endif

