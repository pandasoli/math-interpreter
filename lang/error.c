#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./error.h"


char *Error_throw(struct Error *self, const char *msg, const int pos, const int len) {
  self->err = true;
  char *res = calloc(pos + len + strlen(msg) + 1, sizeof(char));

  for (int i = 0; i < pos + 2; i++) strcat(res, " ");
  for (int i = 0; i < len; i++) strcat(res, "^");

  strcat(res, "\n");
  strcat(res, msg);

  return res;
}


struct Error newError() {
  struct Error res;

  res.err = false;
  res.throw_ = &Error_throw;

  return res;
}

