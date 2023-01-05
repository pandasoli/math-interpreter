#pragma once
#include <stdbool.h>


#ifndef ERROR
#define ERROR

struct Error {
  bool err;

  char *(*throw_)(struct Error *, const char *, const int, const int);
};

#endif

struct Error newError();

